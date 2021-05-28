#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace ImGui
{
	void Spinner(float radius, float thickness, int num_segments, ImVec4 color)
	{
		auto window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		auto& g = *GImGui;
		const auto& style = g.Style;
		auto&& pos = ImGui::GetCursorPos();
		const ImVec2 size(radius * 2, radius * 2);
		const ImVec2 max(pos.x + size.x, pos.y + size.y);
		const ImRect bb(pos, max);
		
		ImGui::ItemSize(bb);
		if (!ImGui::ItemAdd(bb, 0))
			return;

		window->DrawList->PathClear();
		int start = static_cast<int>(fabsf(ImSin(static_cast<float>(g.Time * 1.8f)) * (num_segments - 5)));
		const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
		const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;
		const auto&& centre = ImVec2(pos.x + radius, pos.y + radius);
		for (auto i = 0; i < num_segments; i++)
		{
			const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
			auto time = static_cast<float>(g.Time);
			window->DrawList->PathLineTo({ centre.x + ImCos(a + time * 8) * radius,
										  centre.y + ImSin(a + time * 8) * radius });
		}
		window->DrawList->PathStroke(ImGui::GetColorU32(color), false, thickness);
	}
}
