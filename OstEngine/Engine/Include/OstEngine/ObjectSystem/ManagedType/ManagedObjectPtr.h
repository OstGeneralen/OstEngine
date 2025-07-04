// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/ManagedType/ManagedObjectType.h>
#include <OstEngine/ObjectSystem/ManagedType/ManagedTypeContainerBase.h>
#include <type_traits>

namespace ost
{
	struct TPtrCast;

	template<TOstManagedType T>
	class TPtr
	{
	public:
		TPtr()
			: _stableIdx{ managed_type_constants::STABLE_IDX_INVALID }
			, _pContainer{ nullptr }
		{
		}
		TPtr(uint32 stableIdx, CManagedTypeContainerBase* containerPtr)
			: _stableIdx{ stableIdx }
			, _pContainer{ containerPtr }
		{
			if (Valid())
			{
				Internal_MODHandler::RefIncr(_pContainer->GetManagedObjectData(_stableIdx));
			}
		}
		TPtr(const TPtr& p)
			: _stableIdx{ p._stableIdx }
			, _pContainer{ p._pContainer }
		{
			if (Valid())
			{
				Internal_MODHandler::RefIncr(_pContainer->GetManagedObjectData(_stableIdx));
			}
		}
		TPtr(TPtr&& p) noexcept
			: _stableIdx{ p._stableIdx }
			, _pContainer{ p._pContainer }
		{
			p._stableIdx = managed_type_constants::STABLE_IDX_INVALID;
			p._pContainer = nullptr;
		}
		~TPtr()
		{
			if (Valid())
			{
				Internal_MODHandler::RefDecr(_pContainer->GetManagedObjectData(_stableIdx));
			}
		}

		bool MatchContainerStorageTypeID(uint64 tid) const
		{
			return Valid() && _pContainer->GetContainerStorageTypeID() == tid;
		}
		
		bool operator==(const TPtr<T>& p) const
		{
			return Valid() && p.Valid() && p._stableIdx == _stableIdx && p._pContainer == _pContainer;
		}

		template<TOstManagedType T2>
		bool operator==(const TPtr<T2>& p) const
		{
			return Valid() && p.Valid() && p._stableIdx == _stableIdx && p._pContainer == _pContainer;
		}

		template<TOstManagedType T2> requires std::is_base_of_v<T, T2>
		TPtr& operator=(const TPtr<T2>& p)
		{
			if (Valid())
			{
				Internal_MODHandler::RefDecr(_pContainer->GetManagedObjectData(_stableIdx));
			}
			_stableIdx = p._stableIdx;
			_pContainer = p._pContainer;
			if (Valid())
			{
				Internal_MODHandler::RefIncr(_pContainer->GetManagedObjectData(_stableIdx));
			}
		}

		TPtr& operator=(const TPtr& p)
		{
			if (Valid())
			{
				Internal_MODHandler::RefDecr(_pContainer->GetManagedObjectData(_stableIdx));
			}
			_stableIdx = p._stableIdx;
			_pContainer = p._pContainer;
			if (Valid())
			{
				Internal_MODHandler::RefIncr(_pContainer->GetManagedObjectData(_stableIdx));
			}
			return *this;
		}
		TPtr& operator=(TPtr&& p) noexcept
		{
			if (Valid())
			{
				Internal_MODHandler::RefDecr(_pContainer->GetManagedObjectData(_stableIdx));
			}
			_stableIdx = p._stableIdx;
			_pContainer = p._pContainer;
			p._stableIdx = managed_type_constants::STABLE_IDX_INVALID;
			p._pContainer = nullptr;
			return *this;
		}

		T* operator->() { return GetPtr(); }
		const T* operator->() const { return GetPtr(); }

		T& operator*(int) { return *GetPtr(); }
		const T& operator*(int) const { return *GetPtr(); }

		bool Valid() const
		{
			return _stableIdx != managed_type_constants::STABLE_IDX_INVALID && _pContainer != nullptr;
		}
		operator bool() const
		{
			return Valid();
		}
	private:
		template<TOstManagedType T2>
		friend class TPtr;
		friend struct TPtrCast;

		T* GetPtr()
		{
			return  static_cast<T*>(_pContainer->GetRawObjectPtr(_stableIdx));
		}
		const T* GetPtr() const
		{
			return static_cast<const T*>(_pContainer->GetRawObjectPtr(_stableIdx));
		}

		uint32 _stableIdx;
		CManagedTypeContainerBase* _pContainer;
	};

	struct TPtrCast
	{
		template<TOstManagedType TCastFrom, TOstManagedType TCastTo>
		static TPtr<TCastTo> Static(const TPtr<TCastFrom>& t)
		{
			return TPtr<TCastTo>(t._stableIdx, t._pContainer);
		}
	};

}