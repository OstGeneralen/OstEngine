// Kasper "OstGeneralen" Esbjornsson - 2026
#include "PropertyEditorDrawer.h"

#include "PropertyEditors/BasicTypeEditors.h"
#include "PropertyEditors/GraphicsResourceTypeEditors.h"
#include "PropertyEditors/MathTypeEditors.h"

using namespace ost;

// ------------------------------------------------------------

PropertyEditorDrawer::PropertyEditorDrawer()
{
    _editors.Insert(TypeID::Get<Float32>(), &FLOAT32_PROPERTY_EDITOR);
    _editors.Insert(TypeID::Get<Int32>(), &INT32_PROPERTY_EDITOR);
    _editors.Insert(TypeID::Get<Vector2f>(), &VEC2F_PROPERTY_EDITOR);
    _editors.Insert(TypeID::Get<Vector3f>(), &VEC3F_PROPERTY_EDITOR);
    _editors.Insert(TypeID::Get<Vector4f>(), &VEC4F_PROPERTY_EDITOR);
    _editors.Insert(TypeID::Get<Color>(), &COLOR_PROPERTY_EDITOR);
    _editors.Insert(TypeID::Get<std::string>(), &STRING_PROPERTY_EDITOR);
    _editors.Insert(TypeID::Get<Radians>(), &RADIANS_PROPERTY_EDITOR);
    _editors.Insert(TypeID::Get<HModel>(), &MODEL_HANDLE_PROPERTY_EDITOR);
}

void ost::PropertyEditorDrawer::Draw(TypeID type, const char* name, void* pValue)
{
    if (PropertyEditor** ppEditor = _editors.TryGetValue(type))
    {
        (*ppEditor)->DisplayGeneric(name, pValue);
    }
    else
    {
        ImGui::TextColored({1, 0, 0, 1}, "Unsupported Property Type");
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------