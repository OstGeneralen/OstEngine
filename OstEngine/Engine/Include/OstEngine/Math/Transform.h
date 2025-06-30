// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson(MIT License)
#pragma once
#include <OstEngine/Math/Structures/Vectors.h>
#include <OstEngine/Math/Structures/Quaternion.h>
#include <OstEngine/Math/Structures/Matrices.h>

#include <vector>

namespace ost
{
	enum class ELocality
	{
		Local,
		World,
	};

	class CTransform
	{
	public:
		CTransform();
		CTransform(const CTransform&) = default;

		CTransform* GetParent();
		const CTransform* GetParent() const;

		void AddChild(CTransform& t);
		void RemoveChild(CTransform& t);

		const Matrix4x4f& GetMatrix(ELocality loc = ELocality::Local) const;
		Matrix4x4f GetInverseMatrix(ELocality loc = ELocality::Local) const;

		Vector3f GetPosition(ELocality loc = ELocality::World) const;
		Vector3f GetScale(ELocality loc = ELocality::World) const;
		Quaternion32f GetRotation(ELocality loc = ELocality::World) const;

		CTransform& SetPosition(const Vector3f& pos, ELocality loc = ELocality::World);
		CTransform& SetScale(const Vector3f& scale, ELocality loc = ELocality::World);
		CTransform& SetRotation(const Quaternion32f& rotation, ELocality loc = ELocality::World);

		CTransform& Move(const Vector3f& offset, ELocality loc = ELocality::World);
		CTransform& Scale(const Vector3f& factor, ELocality loc = ELocality::World);
		CTransform& Rotate(const Quaternion32f& factor, ELocality loc = ELocality::World);

	private:
		void MarkLocalDirty();
		void MarkWorldDirty();

		// These recalc functions are marked const to allow being called from the Getters
		// This is the same reason that the cached matrices are mutable
		void RecalcWorldMatrix() const;
		void RecalcLocalMatrix() const;

		Vector3f _translation;
		Quaternion32f _rotation;
		Vector3f _scale;

		CTransform* _parent;
		std::vector<CTransform*> _children;

		mutable Matrix4x4f _localMatrix;
		mutable Matrix4x4f _worldMatrix;

		mutable bool _localDirty;
		mutable bool _worldDirty;
	};
}