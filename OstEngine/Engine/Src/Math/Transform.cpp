// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson(MIT License)
#include <OstEngine/Math/Transform.h>
#include <algorithm>

// ------------------------------------------------------------

ost::CTransform::CTransform()
	: _translation{}
	, _rotation{}
	, _scale{ 1,1,1 }
	, _parent{ nullptr }
	, _children{}
	, _localMatrix{}
	, _worldMatrix{}
	, _localDirty{ false } // Default dirty flags to false since the default
	, _worldDirty{ false } // transform is equal to identity
{
}

// ------------------------------------------------------------

ost::CTransform::CTransform(CTransform&& t) noexcept
	: _translation{ std::move(t._translation) }
	, _rotation{ std::move(t._rotation) }
	, _scale{ std::move(t._scale) }
	, _parent{ t._parent }
	, _children{ std::move(t._children) }
	, _localMatrix{ std::move(t._localMatrix) }
	, _worldMatrix{ std::move(t._worldMatrix) }
	, _localDirty{ t._localDirty }
	, _worldDirty{ t._worldDirty }
{
	if (_parent != nullptr)
	{
		for (auto& childOfParent : _parent->_children)
		{
			if (childOfParent == &t)
			{
				childOfParent = this;
				break;
			}
		}
	}

	for (auto childPtr : _children)
	{
		childPtr->_parent = this;
	}

	t._parent = nullptr;
	t._children.clear();
}

// ------------------------------------------------------------

ost::CTransform& ost::CTransform::operator=(CTransform&& t) noexcept
{
	_translation = std::move(t._translation);
	_scale = std::move(t._scale);
	_parent = t._parent;
	_children = std::move(t._children);
	_localMatrix = std::move(t._localMatrix);
	_worldMatrix = std::move(t._worldMatrix);
	_localDirty = t._localDirty;
	_worldDirty = t._worldDirty;

	if (_parent != nullptr)
	{
		for (auto& childOfParent : _parent->_children)
		{
			if (childOfParent == &t)
			{
				childOfParent = this;
				break;
			}
		}
	}

	for (auto childPtr : _children)
	{
		childPtr->_parent = this;
	}

	t._parent = nullptr;
	t._children.clear();
	return *this;
}

// ------------------------------------------------------------

ost::CTransform::~CTransform()
{
	if (_parent != nullptr)
	{
		_parent->RemoveChild(*this);
	}

	// Any children becomes root objects now
	for (auto childPtr : _children)
	{
		childPtr->_parent = nullptr;
		childPtr->MarkWorldDirty();
	}
}

	// ------------------------------------------------------------

	ost::CTransform* ost::CTransform::GetParent()
	{
		return _parent;
	}

	// ------------------------------------------------------------

	const ost::CTransform* ost::CTransform::GetParent() const
	{
		return _parent;
	}

	// ------------------------------------------------------------

	void ost::CTransform::AddChild(CTransform& t)
	{
		if (t._parent != nullptr)
		{
			t._parent->RemoveChild(t);
		}
		_children.push_back(&t);
		t._parent = this;
		t.MarkWorldDirty();
	}

	// ------------------------------------------------------------

	void ost::CTransform::RemoveChild(CTransform& t)
	{
		std::vector<CTransform*>::iterator it = std::find_if(_children.begin(), _children.end(), [&](CTransform* ptr) { return ptr == &t; });
		if (it != _children.end())
		{
			(*it)->_parent = nullptr;
			(*it)->MarkWorldDirty();
			_children.erase(it);

		}
	}

	// ------------------------------------------------------------

	const ost::Matrix4x4f& ost::CTransform::GetMatrix(ELocality loc) const
	{
		switch (loc)
		{
		case ost::ELocality::Local:
		{
			if (_localDirty)
			{
				RecalcLocalMatrix();
			}
			return _localMatrix;
		}
		case ost::ELocality::World:
		{
			if (_worldDirty)
			{
				RecalcWorldMatrix();
			}
			return _worldMatrix;
		}
		}

		return Matrix4x4f(); // We should never reach this code
	}

	// ------------------------------------------------------------

	ost::Matrix4x4f ost::CTransform::GetInverseMatrix(ELocality loc) const
	{
		return GetMatrix(loc).GetFastInverse();
	}

	// ------------------------------------------------------------

	ost::Vector3f ost::CTransform::GetPosition(ELocality loc) const
	{
		if (loc == ELocality::World)
		{
			// Getter over member access to ensure dirty check and recalc
			auto& worldMat = GetMatrix(ELocality::World);
			return Vector3f(worldMat.Elements[12], worldMat.Elements[13], worldMat.Elements[14]);
		}
		return _translation;
	}

	// ------------------------------------------------------------

	ost::Quaternion32f ost::CTransform::GetRotation(ELocality loc) const
	{
		if (loc == ELocality::World)
		{
			// Getter over member access to ensure dirty check and recalc
			auto& worldMat = GetMatrix(ELocality::World);

			const Vector4f c1v4 = worldMat.GetCol1();
			const Vector4f c2v4 = worldMat.GetCol2();
			const Vector4f c3v4 = worldMat.GetCol3();

			const Vector3f c1n = Vector3f{ c1v4.X, c1v4.Y, c1v4.Z }.GetNormalized();
			const Vector3f c2n = Vector3f{ c2v4.X, c2v4.Y, c2v4.Z }.GetNormalized();
			const Vector3f c3n = Vector3f{ c3v4.X, c3v4.Y, c3v4.Z }.GetNormalized();

			Matrix4x4f rotMat;
			rotMat.Elements[0] = c1n.X;
			rotMat.Elements[1] = c1n.Y;
			rotMat.Elements[2] = c1n.Z;

			rotMat.Elements[4] = c2n.X;
			rotMat.Elements[5] = c2n.Y;
			rotMat.Elements[6] = c2n.Z;

			rotMat.Elements[8] = c3n.X;
			rotMat.Elements[9] = c3n.Y;
			rotMat.Elements[10] = c3n.Z;

			return Quaternion32f::FromRotationMatrix(rotMat);
		}

		return _rotation;
	}

	// ------------------------------------------------------------

	ost::Vector3f ost::CTransform::GetScale(ELocality loc) const
	{
		if (loc == ELocality::World)
		{
			// Getter over member access to ensure dirty check and recalc
			auto& worldMat = GetMatrix(ELocality::World);
			const Vector3f xs{ worldMat.Elements[0], worldMat.Elements[1], worldMat.Elements[2] };
			const Vector3f ys{ worldMat.Elements[4], worldMat.Elements[5], worldMat.Elements[6] };
			const Vector3f zs{ worldMat.Elements[8], worldMat.Elements[9], worldMat.Elements[10] };
			return Vector3f{ xs.Magnitude(), ys.Magnitude(), zs.Magnitude() };
		}

		return _scale;
	}

	// ------------------------------------------------------------

	ost::CTransform& ost::CTransform::SetPosition(const Vector3f& pos, ELocality loc)
	{
		if (loc == ELocality::World && _parent != nullptr)
		{
			const Matrix4x4f parentInv = _parent->GetInverseMatrix();
			const Vector4f posv4{ pos, 1.0f };
			_translation = Vector_Cast<Vector3f>(parentInv * posv4);
		}
		else // Set for local OR does not have parent
		{
			_translation = pos;
		}
		MarkLocalDirty();
		return *this;
	}

	// ------------------------------------------------------------

	ost::CTransform& ost::CTransform::SetRotation(const Quaternion32f& rot, ELocality loc)
	{
		if (loc == ELocality::World && _parent != nullptr)
		{
			const Quaternion32f invParentRotation = _parent->GetRotation(ELocality::World).Inverse();
			_rotation = invParentRotation * rot;
		}
		else // Set for local OR does not have parent
		{
			_rotation = rot;
		}
		MarkLocalDirty();
		return *this;
	}

	// ------------------------------------------------------------

	ost::CTransform& ost::CTransform::SetScale(const Vector3f& scale, ELocality loc)
	{
		if (loc == ELocality::World && _parent != nullptr)
		{
			const Vector3f parentWorldScale = _parent->GetScale(ELocality::World);
			Vector3f nScale{ 1.0f, 1.0f, 1.0f };

			if (parentWorldScale.X != 0.0f)
			{
				nScale.X = scale.X / parentWorldScale.X;
			}
			if (parentWorldScale.Y != 0.0f)
			{
				nScale.Y = scale.Y / parentWorldScale.Y;
			}
			if (parentWorldScale.Z != 0.0f)
			{
				nScale.Z = scale.Z / parentWorldScale.Z;
			}
			_scale = nScale;
		}
		else // Set for local OR does not have parent
		{
			_scale = scale;
		}
		MarkLocalDirty();
		return *this;
	}

	// ------------------------------------------------------------

	ost::CTransform& ost::CTransform::Move(const Vector3f& offset, ELocality loc)
	{
		SetPosition(GetPosition(loc) + offset, loc);
		return *this;
	}

	// ------------------------------------------------------------

	ost::CTransform& ost::CTransform::Rotate(const Quaternion32f& rot, ELocality loc)
	{
		if (loc == ELocality::World && _parent != nullptr)
		{
			const Quaternion32f worldRot = rot * GetRotation(ELocality::World);
			SetRotation(worldRot, ELocality::World);
		}
		else
		{
			_rotation = _rotation * rot;
			MarkLocalDirty();
		}
		return *this;
	}

	// ------------------------------------------------------------

	ost::CTransform& ost::CTransform::Scale(const Vector3f& s, ELocality loc)
	{
		const Vector3f currentLocScale = GetScale(loc);
		SetScale(Vector3f{ currentLocScale.X * s.X, currentLocScale.Y * s.Y, currentLocScale.Z * s.Z }, loc);
		return *this;
	}

	// ------------------------------------------------------------

	void ost::CTransform::MarkLocalDirty()
	{
		_localDirty = true;
		for (auto c : _children)
		{
			c->MarkWorldDirty();
		}
	}

	// ------------------------------------------------------------

	void ost::CTransform::MarkWorldDirty()
	{
		_worldDirty = true;
		for (auto c : _children)
		{
			c->MarkWorldDirty();
		}
	}

	// ------------------------------------------------------------

	void ost::CTransform::RecalcWorldMatrix() const
	{
		if (_parent)
		{
			_worldMatrix = _parent->GetMatrix(ELocality::World) * GetMatrix(ELocality::Local);
		}
		else
		{
			_worldMatrix = GetMatrix(ELocality::Local);
		}
		_worldDirty = false;
	}

	// ------------------------------------------------------------

	void ost::CTransform::RecalcLocalMatrix() const
	{
		_localMatrix = Matrix4x4f::CreateTranslation(_translation) * _rotation.ToRotationMatrix() * Matrix4x4f::CreateScale(_scale);
		_localDirty = false;
	}

	// ------------------------------------------------------------
	// ------------------------------------------------------------
	// ------------------------------------------------------------