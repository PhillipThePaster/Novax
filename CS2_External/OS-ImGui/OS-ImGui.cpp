#pragma once
#include "OS-ImGui.h"
#include <Shellapi.h>
#include <Windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// OS-ImGui Draw
namespace OSImGui
{
    bool OSImGui::LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
    { //shit coded by sysR@M
        int image_width = 0;
        int image_height = 0;
        unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
        if (image_data == NULL)
            return false;
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = image_width;
        desc.Height = image_height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;
        ID3D11Texture2D* pTexture = NULL;
        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = image_data;
        subResource.SysMemPitch = desc.Width * 4;
        subResource.SysMemSlicePitch = 0;
        g_Device.g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);
        // Create texture view
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        g_Device.g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
        pTexture->Release();
        *out_width = image_width;
        *out_height = image_height;
        stbi_image_free(image_data);
        return true;
    }

    bool OSImGui::LoadTextureFromMemory(unsigned char* Memory, UINT size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
    {
        int image_width = 0;
        int image_height = 0;
        unsigned char* image_data = stbi_load_from_memory(Memory, size, &image_width, &image_height, NULL, 4);
        if (image_data == NULL)
            return false;
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = image_width;
        desc.Height = image_height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;
        ID3D11Texture2D* pTexture = NULL;
        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = image_data;
        subResource.SysMemPitch = desc.Width * 4;
        subResource.SysMemSlicePitch = 0;
        g_Device.g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);
        // Create texture view
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        g_Device.g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
        pTexture->Release();
        *out_width = image_width;
        *out_height = image_height;
        stbi_image_free(image_data);
        return true;
    }

    void OSImGui::ShowRawImage(unsigned char* image, int width, int height)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return;

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 pos = ImGui::GetCursorScreenPos();

        // Render image
        draw_list->AddImage(
            (void*)image,
            ImVec2(pos.x + width, pos.y + height),
            ImVec2(0, 0),
            ImVec2(1, 1)
        );
        // Update cursor pos
        ImGui::Dummy(ImVec2(width, height));
    }


    void OSImGui::MyProgressBar(float fraction, const ImVec2& Size, const char* overlay, ImVec4 Color)
    {
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, Color);
        ImGui::ProgressBar(fraction, Size, overlay);
        ImGui::PopStyleColor();
    }

  
    void OSImGui::MyText(std::string Text, bool isCenter) {
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize(Text.c_str()).x;
        if (isCenter)
            ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(Text.c_str());
    }

    void OSImGui::Text(std::string Text, Vec2 Pos, ImColor Color, float FontSize, bool KeepCenter)
    {
        if (!KeepCenter)
        {
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos.ToImVec2(), Color, Text.c_str());
        }
        else
        {
            float TextWidth = ImGui::GetFont()->CalcTextSizeA(FontSize, FLT_MAX, 0.f, Text.c_str()).x;
            ImVec2 Pos_ = { Pos.x - TextWidth / 2,Pos.y };
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos_, Color, Text.c_str());
        }
    }


    void OSImGui::StrokeText(std::string Text, Vec2 Pos, ImColor Color, float FontSize, bool KeepCenter)
    {
        this->Text(Text, Vec2(Pos.x - 1, Pos.y + 1), ImColor(0, 0, 0), FontSize, KeepCenter);
        this->Text(Text, Vec2(Pos.x - 1, Pos.y - 1), ImColor(0, 0, 0), FontSize, KeepCenter);
        this->Text(Text, Vec2(Pos.x + 1, Pos.y + 1), ImColor(0, 0, 0), FontSize, KeepCenter);
        this->Text(Text, Vec2(Pos.x + 1, Pos.y - 1), ImColor(0, 0, 0), FontSize, KeepCenter);
        this->Text(Text, Pos, Color, FontSize, KeepCenter);
    }

    void OSImGui::Rectangle(Vec2 Pos, Vec2 Size, ImColor Color, float Thickness, float Rounding)
    {
        ImGui::GetBackgroundDrawList()->AddRect(Pos.ToImVec2(), { Pos.x + Size.x,Pos.y + Size.y }, Color, Rounding, 0, Thickness);
    }

    void OSImGui::RectangleFilled(Vec2 Pos, Vec2 Size, ImColor Color, float Rounding, int Nums)
    {
        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
        ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All;
        ImVec2 a = Pos.ToImVec2();
        ImVec2 b = { Pos.x + Size.x,Pos.y + Size.y };
        Rounding = ImMin<float>(Rounding, fabsf(Size.x) * (((rounding_corners & ImDrawCornerFlags_Top) == ImDrawCornerFlags_Top) || ((rounding_corners & ImDrawCornerFlags_Bot) == ImDrawCornerFlags_Bot) ? 0.5f : 1.0f) - 1.0f);
        Rounding = ImMin<float>(Rounding, fabsf(Size.y) * (((rounding_corners & ImDrawCornerFlags_Left) == ImDrawCornerFlags_Left) || ((rounding_corners & ImDrawCornerFlags_Right) == ImDrawCornerFlags_Right) ? 0.5f : 1.0f) - 1.0f);

        if (Rounding <= 0.0f || rounding_corners == 0)
        {
            DrawList->PathLineTo(a);
            DrawList->PathLineTo(ImVec2(b.x, a.y));
            DrawList->PathLineTo(b);
            DrawList->PathLineTo(ImVec2(a.x, b.y));
        }
        else
        {
            DrawList->PathArcTo(ImVec2(a.x + Rounding, a.y + Rounding), Rounding, IM_PI, IM_PI / 2.f * 3.f, Nums);
            DrawList->PathArcTo(ImVec2(b.x - Rounding, a.y + Rounding), Rounding, IM_PI / 2.f * 3.f, IM_PI * 2.f, Nums);
            DrawList->PathArcTo(ImVec2(b.x - Rounding, b.y - Rounding), Rounding, 0.f, IM_PI / 2.f, Nums);
            DrawList->PathArcTo(ImVec2(a.x + Rounding, b.y - Rounding), Rounding, IM_PI / 2.f, IM_PI, Nums);
        }
        DrawList->PathFillConvex(Color);
    }

    void OSImGui::RectangleFilledGraident(Vec2 Pos, Vec2 Size, ImColor BgColor, ImColor TopColor, ImColor BotColor, float Rounding, int Nums)
    {
        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
        ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All;
        ImVec2 a = Pos.ToImVec2();
        ImVec2 b = { Pos.x + Size.x,Pos.y + Size.y };

        Rounding = ImMin<float>(Rounding, fabsf(Size.x) * (((rounding_corners & ImDrawCornerFlags_Top) == ImDrawCornerFlags_Top) || ((rounding_corners & ImDrawCornerFlags_Bot) == ImDrawCornerFlags_Bot) ? 0.5f : 1.0f) - 1.0f);
        Rounding = ImMin<float>(Rounding, fabsf(Size.y) * (((rounding_corners & ImDrawCornerFlags_Left) == ImDrawCornerFlags_Left) || ((rounding_corners & ImDrawCornerFlags_Right) == ImDrawCornerFlags_Right) ? 0.5f : 1.0f) - 1.0f);

        //DrawList->AddRectFilledMultiColorRounded(a, b, BgColor, TopColor, TopColor, BotColor, BotColor, Rounding, rounding_corners);
    }

    void OSImGui::Line(Vec2 From, Vec2 To, ImColor Color, float Thickness)
    {
        ImGui::GetBackgroundDrawList()->AddLine(From.ToImVec2(), To.ToImVec2(), Color, Thickness);
    }

    void OSImGui::LineGlow(Vec2 From, Vec2 To, ImColor Color, float Thickness)
    { // https://yougame.biz/threads/299495/#post-2961450
        /*float dynamicAlpha = 255.f;
        float lineThickness = 15.0f; //start with whatever value you want and it will decrease by the value of thicknessStep for each iteration

        for (int i = 0; i < numLines; ++i) {

            Renderer.Line(prev_screen, cur_screen, ImColor(baseColor.Value.x, baseColor.Value.y, baseColor.Value.z, dynamicAlpha), lineThickness);

            dynamicAlpha -= alphaStep;
            if (dynamicAlpha <= 0) {
                break;
            }

            lineThickness -= thicknessStep;
        }*/

        this->Line(From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w), Thickness + 1.f);
        this->Line(From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w * 0.4f), Thickness + 3.f);
        this->Line(From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w * 0.2f), Thickness + 5.f);
        this->Line(From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w * 0.09f), Thickness + 8.f);
        this->Line(From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w * 0.02f), Thickness + 11.f);
        this->Line(From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w * 0.004f), Thickness + 14.f);
    }

    void OSImGui::CircleGradient(const Vec2 center, float radius, ImColor col_in, ImColor col_out) {
        if (((col_in | col_out) & IM_COL32_A_MASK) == 0 || radius < 0.5f)
            return;

        ImGui::GetBackgroundDrawList()->_PathArcToFastEx(ImVec2(center.x, center.y), radius, 0, IM_DRAWLIST_ARCFAST_SAMPLE_MAX, 0);
        const int count = ImGui::GetBackgroundDrawList()->_Path.Size - 1;

        unsigned int vtx_base = ImGui::GetBackgroundDrawList()->_VtxCurrentIdx;
        ImGui::GetBackgroundDrawList()->PrimReserve(count * 3, count + 1);

        const ImVec2 uv = ImGui::GetBackgroundDrawList()->_Data->TexUvWhitePixel;
        ImGui::GetBackgroundDrawList()->PrimWriteVtx(ImVec2(center.x, center.y), uv, col_in);
        for (int n = 0; n < count; n++)
            ImGui::GetBackgroundDrawList()->PrimWriteVtx(ImGui::GetBackgroundDrawList()->_Path[n], uv, col_out);

        for (int n = 0; n < count; n++)
        {
            ImGui::GetBackgroundDrawList()->PrimWriteIdx((ImDrawIdx)(vtx_base));
            ImGui::GetBackgroundDrawList()->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + n));
            ImGui::GetBackgroundDrawList()->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + ((n + 1) % count)));
        }
        ImGui::GetBackgroundDrawList()->_Path.Size = 0;
    }


    void OSImGui::Circle(Vec2 Center, float Radius, ImColor Color, float Thickness, int Num)
    {
        ImGui::GetBackgroundDrawList()->AddCircle(Center.ToImVec2(), Radius, Color, Num, Thickness);
    }

    void OSImGui::CircleFilled(Vec2 Center, float Radius, ImColor Color, int Num)
    {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(Center.ToImVec2(), Radius, Color, Num);
    }

    void OSImGui::ConnectPoints(std::vector<Vec2> Points, ImColor Color, float Thickness)
    {
        if (Points.size() <= 0)
            return;
        for (int i = 0; i < Points.size() - 1; i++)
        {
            Line(Points[i], Points[i + 1], Color, Thickness);
            if (i == Points.size() - 2)
                Line(Points[i + 1], Points[0], Color, Thickness);
        }
    }

    void OSImGui::Arc(ImVec2 Center, float Radius, ImColor Color, float Thickness, float Angle_begin, float Angle_end, float Nums)
    {
        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
        float angle = (Angle_end - Angle_begin) / Nums;
        for (int i = 0; i < Nums; i++)
        {
            float angle_ = i * angle + Angle_begin - IM_PI / 2;
            DrawList->PathLineTo({ Center.x - Radius * cos(angle_),Center.y - Radius * sin(angle_) });
        }
        DrawList->PathStroke(Color, false, Thickness);
    }

    void OSImGui::ShadowRectFilled(Vec2 Pos, Vec2 Size, ImColor RectColor, ImColor ShadowColor, float ShadowThickness, Vec2 ShadowOffset, float Rounding)
    {
        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
        ImDrawFlags Flags = (Rounding > 0.f) ? ImDrawFlags_RoundCornersMask_ : ImDrawFlags_None;
        DrawList->AddShadowRect(Pos.ToImVec2(), { Pos.x + Size.x,Pos.y + Size.y }, ShadowColor, ShadowThickness, ShadowOffset.ToImVec2(), Flags, Rounding);
        DrawList->AddRectFilled(Pos.ToImVec2(), { Pos.x + Size.x,Pos.y + Size.y }, RectColor, Rounding);
    }

    void OSImGui::ShadowCircle(Vec2 Pos, float Radius, ImColor CircleColor, ImColor ShadowColor, float ShadowThickness, Vec2 ShadowOffset, int Num)
    {
        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
        DrawList->AddShadowCircle(Pos.ToImVec2(), Radius, ShadowColor, ShadowThickness, ShadowOffset.ToImVec2(), ImDrawFlags_None, Num);
        DrawList->AddCircleFilled(Pos.ToImVec2(), Radius, CircleColor, Num);
    }


    bool OSImGui::Slider(const char* label, ImGuiDataType data_type, void* p_data, float p_min, float p_max, const char* format, ImU32 Theme, ImGuiSliderFlags flags)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const float w = ImGui::CalcItemWidth();

        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        const ImRect frame_bb(window->DC.CursorPos, (Vec2(window->DC.CursorPos) + Vec2(w, label_size.y + style.FramePadding.y * 2.0f)).ToImVec2());
        const ImRect total_bb(frame_bb.Min, (Vec2(frame_bb.Max) + Vec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f)).ToImVec2());

        const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id, &frame_bb, temp_input_allowed ? ImGuiItemFlags_Inputable : 0))
            return false;

        // Default format string when passing NULL
        if (format == NULL)
            format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;

        const bool hovered = ImGui::ItemHoverable(frame_bb, id);
        bool temp_input_is_active = temp_input_allowed && ImGui::TempInputIsActive(id);
        if (!temp_input_is_active)
        {
            // Tabbing or CTRL-clicking on Slider turns it into an input box
            const bool input_requested_by_tabbing = temp_input_allowed && (g.LastItemData.StatusFlags & ImGuiItemStatusFlags_FocusedByTabbing) != 0;
            const bool clicked = hovered && ImGui::IsMouseClicked(0, id);
            const bool make_active = (input_requested_by_tabbing || clicked || g.NavActivateId == id);
            if (make_active && clicked)
                ImGui::SetKeyOwner(ImGuiKey_MouseLeft, id);
            if (make_active && temp_input_allowed)
                if (input_requested_by_tabbing || (clicked && g.IO.KeyCtrl) || (g.NavActivateId == id && (g.NavActivateFlags & ImGuiActivateFlags_PreferInput)))
                    temp_input_is_active = true;

            if (make_active && !temp_input_is_active)
            {
                ImGui::SetActiveID(id, window);
                ImGui::SetFocusID(id, window);
                ImGui::FocusWindow(window);
                g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
            }
        }

        if (temp_input_is_active) {
            // Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
            const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
            return ImGui::TempInputScalar(frame_bb, id, label, data_type, p_data, format, is_clamp_input ? &p_min : NULL, is_clamp_input ? &p_max : NULL);
        }

        float grab_radius = 8;

        // Draw frame
        ImRect frame_sc = frame_bb;
        float frame_height_origin = frame_sc.GetHeight();
        frame_sc.Min.y += frame_height_origin / 3;
        frame_sc.Max.y -= frame_height_origin / 3;
        const ImU32 frame_col = ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
        ImGui::RenderNavHighlight(frame_bb, id);

        float fill_width = frame_bb.Min.x + (frame_bb.GetWidth() * (static_cast<float>(*((float*)p_data)) - p_min) / (p_max - p_min));

        float Back_w = frame_bb.Min.x + (frame_bb.GetWidth() * (p_max - p_min) / (p_max - p_min));
        // Render filled portion
        window->DrawList->AddRect(frame_sc.Min, ImVec2(Back_w, frame_sc.Max.y), frame_col, grab_radius);
        window->DrawList->AddRectFilled(frame_sc.Min, ImVec2(Back_w, frame_sc.Max.y), frame_col, grab_radius);
        window->DrawList->AddRectFilled(frame_sc.Min, ImVec2(fill_width, frame_sc.Max.y), Theme, grab_radius);

        // Slider behavior
        ImRect grab_bb;
        const bool value_changed = ImGui::SliderBehavior(frame_bb, id, data_type, p_data, &p_min, &p_max, format, flags, &grab_bb);
        if (value_changed)
            ImGui::MarkItemEdited(id);

        char value_buf[64];
        const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);
        if (g.LogEnabled)
            ImGui::LogSetNextTextDecoration("{", "}");
        ImGui::RenderTextClipped(frame_bb.Min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));

        // label
        if (label_size.x > 0.0f)
            ImGui::RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | (temp_input_allowed ? ImGuiItemStatusFlags_Inputable : 0));
        return value_changed;
    }
}

