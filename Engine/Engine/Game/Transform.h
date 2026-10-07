// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Container/List.h>
#include <Math/Matrix4x4.h>
#include <Math/Quaternion.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>

// ------------------------------------------------------------

namespace ost
{
    enum class ESpace
    {
        Local,
        World,
    };

    class Transform
    {
    public:
        friend class Actor; // Actors are the owners of transforms!

        void SetWorldPosition(const Vector3f& position)
        {
            if (_parent)
            {
                SetPosition(Vector4f(position, 1.0f) * _parent->GetWorldTransform().GetInverse());
            }
            else
            {
                SetPosition(position);
            }
        }

        void SetPosition(const Vector3f& position)
        {
            _position = position;
            MarkWorldMatrixDirty();
        }

        void SetWorldRotation(const Quaternion& rotation)
        {
            if (_parent)
            {
                SetRotation(rotation * _parent->GetWorldRotation().GetInverse());
            }
            else
            {
                SetRotation(rotation);
            }
        }

        void SetRotation(const Quaternion& rotation)
        {
            _rotation = rotation;
            MarkWorldMatrixDirty();
        }

        void Move(const Vector3f& offset, ESpace space = ESpace::Local)
        {
            switch (space)
            {
            case ESpace::Local:
                SetPosition(_position + _rotation.RotateVector(offset));
                break;
            case ESpace::World:
                SetPosition(_position + offset);
                break;
            }
        }

        void Rotate(const Quaternion& rotation)
        {
            SetRotation(_rotation * rotation);
        }

        const Matrix4x4& GetWorldTransform() const
        {
            if (_worldMatrixDirty)
            {
                RecalculateCachedWorldMatrix();
                _worldMatrixDirty = false;
            }
            return _cachedWorldMatrix;
        }

        const Vector3f& GetPosition() const
        {
            return _position;
        }
        const Quaternion& GetRotation() const
        {
            return _rotation;
        }

        Vector3f GetWorldPosition() const
        {
            if (_parent)
            {
                return Vector4f(_position, 1.0f) * _parent->GetWorldTransform();
            }
            return _position;
        }
        Quaternion GetWorldRotation() const
        {
            if (_parent)
            {
                return _rotation * _parent->GetWorldRotation();
            }
            return _rotation;
        }

    private:
        void MarkWorldMatrixDirty()
        {
            if (_worldMatrixDirty)
            {
                // Early out here. If we're already at a dirty world matrix, let's not traverse hierarchy again.
                return;
            }

            _worldMatrixDirty = true;
            for (auto c : _children)
            {
                c->MarkWorldMatrixDirty();
            }
        }

        void RecalculateCachedWorldMatrix() const
        {
            _cachedWorldMatrix = Matrix4x4::CreateTransformMatrix(_position, _rotation);
            if (_parent)
            {
                _cachedWorldMatrix *= _parent->GetWorldTransform();
            }
        }

        void SetParent(Transform* parent)
        {
            if (_parent)
            {
                for (SizeType i = 0; i < _parent->_children.GetSize(); ++i)
                {
                    if (_parent->_children[i] == this)
                    {
                        _parent->_children.Remove(i);
                        break;
                    }
                }
            }

            _parent = parent;

            if (_parent)
            {
                _parent->_children.Add(this);
            }

            MarkWorldMatrixDirty();
        }

        Transform* _parent = nullptr;
        List<Transform*> _children;

        Vector3f _position;
        Quaternion _rotation;

        mutable Matrix4x4 _cachedWorldMatrix;
        mutable bool _worldMatrixDirty = false;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------