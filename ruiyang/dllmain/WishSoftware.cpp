#include "WishSoftware.h"
#include <imgui_internal.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileDialog.h"
#include <GL/gl3w.h>            // GL3w, initialized with gl3wInit() below
#include <GLFW/glfw3.h> // 引入GLFW库
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include "..\..\ThirdParty\pugixml\pugiconfig.hpp"
#include "..\..\ThirdParty\pugixml\pugixml.hpp"
#include "mini/ini.h"

// 假设这是一个全局变量，用于存储初始目录
//static std::string g_LastDirectory = "."; // 替换为你的默认路

WishSoftware::WishSoftware()
{
	currentRowCount = 0;
	product_rows.clear();
	price_data.clear();
	show_main_window = false;
	button_priceSave_clicked = false;
	show_price_setting_window = false;
	show_product_setting_window = false;
	show_param_setting_window = false;
	show_product_xlsx = false;
	show_sale_xlsx = false;
	opt_fullscreen = true;
	selection = -1;
	price_whole = 0;
	frame_width_threshold = 35;
	m_priceData_fileName = "priceConfig.csv";
	m_productData_fileName= "productConfig.xml";

	//const char*  name1 = u8"德州睿阳纱网厂生产单";
	//// 将 UTF-8 编码的汉字复制到数组中
	//strncpy(textBuffer_name, name1, sizeof(textBuffer_name) - 1);
	//// 确保字符串以空字符结尾
	//textBuffer_name[sizeof(textBuffer_name) - 1] = '\0';

	//const char* name2 = u8"德州睿阳纱网厂随货单";
	//// 将 UTF-8 编码的汉字复制到数组中
	//strncpy(textBuffer_name2, name2, sizeof(textBuffer_name2) - 1);
	//// 确保字符串以空字符结尾
	//textBuffer_name2[sizeof(textBuffer_name2) - 1] = '\0';

	std::string name= u8"德州睿阳纱网厂生产单";
	std::strcpy(textBuffer_name, name.c_str());
	std::string name2= u8"德州睿阳纱网厂随货单";
	std::strcpy(textBuffer_name2, name2.c_str());
	std::string address = u8"德州市临邑县广场大街东首(崔家胡同村荷亭十巷)路南";
	std::strcpy(textBuffer_address, address.c_str());
	std::string phone = u8"(徐):18553406126";
	std::strcpy(textBuffer_phone, phone.c_str());


}

WishSoftware::~WishSoftware()
{
	
}


void WishSoftware::draw_param_setting_window()
{
	ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_FirstUseEver);
	ImGui::Begin(u8"参数设置窗口", &show_param_setting_window);
	{
		//double width_ = ImGui::GetWindowWidth() * (1.0f / 3.0f);
		//ImGui::PushItemWidth(-1);
		//ImGui::InputInt(u8"特殊宽度阈值:", &frame_width_threshold, 0, 0);
		ImGui::NewLine();
		ImGui::PushItemWidth(-1); ImGui::Text(u8"特殊框宽度>阈值(mm):");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##fraw:", &frame_width_threshold, 0, 0);
		ImGui::NewLine();
		ImGui::PushItemWidth(-1); ImGui::Text(u8"特殊框高度>阈值(mm):");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##frahmin:", &frame_height_thmax, 0, 0);
		ImGui::NewLine();
		ImGui::PushItemWidth(-1); ImGui::Text(u8"特殊框高度<阈值(mm):");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##frahmax:", &frame_height_thmin, 0, 0);

		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
		ImGui::PushItemWidth(-1); ImGui::Text(u8"生产单设置: (mm)");
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"标题行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##p1:", &product_table.row1, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"产品行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##p2:", &product_table.row2, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"地址行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##p3:", &product_table.row3, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"序号行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##p4:", &product_table.row4, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"数据行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##pdr:", &product_table.data_row, 0, 0);


		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
		ImGui::PushItemWidth(-1); ImGui::Text(u8"随货单设置: (mm)");
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"表格总长:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##sL:", &sale_table.length, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"标题行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##s1:", &sale_table.row1, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"客户行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##s2:", &sale_table.row2, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"地址行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##s3:", &sale_table.row3, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"序号行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##s4:", &sale_table.row4, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"数据行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##sdr:", &sale_table.data_row, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"计额行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##s5_6:", &sale_table.row5_6, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"生产行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##s7:", &sale_table.row7, 0, 0);
		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"联系行高:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);ImGui::InputInt("##s8:", &sale_table.row8, 0, 0);

	}

	ImGui::NewLine();
	ImGui::Separator();
	ImGui::NewLine();

	if (ImGui::Button((u8"保存"), ImVec2(-1, 0)))
	{
		///write_priceCSV(m_priceData_fileName, price_data);
		//write_productXML();
		write_paramSetting();
	}

	ImGui::End();

}

void WishSoftware::draw_price_style_table()
{
	ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_FirstUseEver);
	ImGui::Begin(u8"价格类型设置窗口", &show_price_setting_window);
	if (ImGui::BeginTable("##Table", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable))
	{
		ImGui::TableSetupColumn(u8"价格类型");
		ImGui::TableSetupColumn(u8"宽Min");
		ImGui::TableSetupColumn(u8"宽Max");
		ImGui::TableSetupColumn(u8"高Min");
		ImGui::TableSetupColumn(u8"高Max");
		ImGui::TableSetupColumn(u8"价格");
		ImGui::TableHeadersRow();
		for (int i = 0; i < price_data.size(); i++)
		{
			ImGui::PushID(i); // 为每行创建一个唯一的ID

			ImGui::TableNextRow();
			// 添加Checkbox
			ImGui::TableSetColumnIndex(0);
			ImGui::Text((u8"价格" + std::to_string(i + 1)).c_str());


			for (int j = 0; j < 5; j++) {
				ImGui::TableSetColumnIndex(j + 1);
				//ImGui::SameLine(); // 保持在同一行
				//ImGui::NextColumn(); // 移动到下一列
				//ImGui::SetNextItemWidth(-FLT_MIN); // 设置输入框宽度自适应
				//ImGui::SetNextItemWidth(item_width); // 设置每个输入框的宽度
				ImGui::PushItemWidth(-1);
				ImGui::InputInt(("##" + std::to_string(j + 1)).c_str(), &price_data[i][j], 0, 0);
				//ImGui::InputInt(NULL, &product_rows[i].data[j], 0, 0);
			}

			ImGui::PopID();

		}
		ImGui::EndTable();
	}
	// 添加和减少行的按钮
	if (ImGui::Button(u8"添加价格类型")) {
		if (price_data.size() < 30)
		{
			price_data.push_back({ 0, 0, 0, 0, 0 });
		}

		//current_product_row++; // 增加行数
	}
	ImGui::SameLine();
	if (price_data.size() > 0 && ImGui::Button(u8"减少价格类型")) {
		price_data.pop_back(); // 删除最后一行;
	}

	ImGui::NewLine();
	if (ImGui::Button((u8"保存"), ImVec2(-1, 0)))
	{
		write_priceCSV(m_priceData_fileName, price_data);
	}
	ImGui::End();

}

void WishSoftware::draw_product_xlxs_window()
{
	////static char textBuffer[256] = ""; // 存储输入框的文本内容
	//ImGui::Begin(u8"生产单导出窗口", &show_product_xlsx);
	//{
	//	ImGui::Text(u8"名称");
	//	ImGui::SameLine();
	//	ImGui::InputText("##", textBuffer, IM_ARRAYSIZE(textBuffer));

	//}
	//ImGui::End();
	// 开始 ImGui 渲染
	//ImGui::Begin("Export File Example",& show_product_xlsx);
	ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_FirstUseEver);
	ImGui::Begin(u8"表单制定窗口", &show_product_xlsx);
	{
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"生产单名称:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##na1", textBuffer_name, IM_ARRAYSIZE(textBuffer_name));

		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"随货单名称:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##na2", textBuffer_name2, IM_ARRAYSIZE(textBuffer_name2));
		//ImGui::SetNextItemWidth(-1); ImGui::InputText("##na2", &textBuffer_str_name2[0], textBuffer_str_name2.size() + 1);

		ImGui::NewLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"客户名称:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##cus", textBuffer_custmor, IM_ARRAYSIZE(textBuffer_custmor));

		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"客户电话:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##cusp", textBuffer_custmor_phone, IM_ARRAYSIZE(textBuffer_custmor_phone));

		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"客户地址:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##cusa", textBuffer_custmor_address, IM_ARRAYSIZE(textBuffer_custmor_address));

		//ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"订单日期:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##Date", &current_date[0], current_date.size() + 1, ImGuiInputTextFlags_ReadOnly);

		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"订单编号:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##or", &order_numer[0], order_numer.size() + 1);

		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"产品编号:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputInt("##psty", &product_rows[selection].p_id,0,0, ImGuiInputTextFlags_ReadOnly);

		//ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"产品颜色:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##color", textBuffer_color, IM_ARRAYSIZE(textBuffer_color));
		//ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"订单备注:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##back", textBuffer_backup, IM_ARRAYSIZE(textBuffer_backup));

		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"联系地址:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##ad", textBuffer_address, IM_ARRAYSIZE(textBuffer_address));

		ImGui::SetNextItemWidth(-1); ImGui::Text(u8"联系电话:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1); ImGui::InputText("##ph", textBuffer_phone, IM_ARRAYSIZE(textBuffer_phone));


		ImGui::NewLine();
		// 如果按钮被按下
		//ImGui::SetNextItemWidth(-1);//Export to XLSX
		if (ImGui::Button(u8"导出表格", ImVec2(-1, 0)))
		{
			// 打开文件对话框，设置对话框的键名、标题、文件过滤器和初始目录
			ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save File", ".xlsx");
		}

		// 显示文件对话框并处理选择结果
		if (ImGuiFileDialog::Instance()->Display("SaveFileDlgKey"))
		{
			// 获取对话框中的目录路径
			//std::string directory;
			// 如果用户选择了文件
			if (ImGuiFileDialog::Instance()->IsOk())
			{
				// 获取选择的文件路径
				//xlsx_file_name = order_numer;
				//g_LastDirectory = ImGuiFileDialog::Instance()->GetCurrentPath();
				xlsx_file_name = ImGuiFileDialog::Instance()->GetFilePathName();
				// 执行保存操作...
				create_xlsx();
			}
			// 关闭文件对话框
			ImGuiFileDialog::Instance()->Close();
		}
	}

	// 结束 ImGui 渲染
	ImGui::End();
}




void WishSoftware::draw_sale_xlxs_window()
{
	
	ImGui::Begin(u8"销售单导出窗口", &show_sale_xlsx);
	{
		//ImGui::SetNextItemWidth(-1); ImGui::Text(u8"名称:");
		//ImGui::SameLine();
		//ImGui::SetNextItemWidth(-1); ImGui::InputText("##na", textBuffer_name, IM_ARRAYSIZE(textBuffer_name));

		//ImGui::NewLine();
		//ImGui::SetNextItemWidth(-1); ImGui::Text(u8"客户名称:");
		//ImGui::SameLine();
		//ImGui::SetNextItemWidth(-1); ImGui::InputText("##cu", textBuffer_custmor, IM_ARRAYSIZE(textBuffer_custmor));
		////ImGui::SameLine();
		//ImGui::SetNextItemWidth(-1); ImGui::Text(u8"日期:");
		//ImGui::SameLine();
		//ImGui::SetNextItemWidth(-1); ImGui::InputText("##Date", &current_date[0], current_date.size() + 1, ImGuiInputTextFlags_ReadOnly);
		////ImGui::SameLine();
		//ImGui::SetNextItemWidth(-1); ImGui::Text(u8"颜色:");
		//ImGui::SameLine();
		//ImGui::SetNextItemWidth(-1); ImGui::InputText("##co", textBuffer_color, IM_ARRAYSIZE(textBuffer_color));
		////ImGui::SameLine();
		//ImGui::SetNextItemWidth(-1); ImGui::Text(u8"备注:");
		//ImGui::SameLine();
		//ImGui::SetNextItemWidth(-1); ImGui::InputText("##ba", textBuffer_backup, IM_ARRAYSIZE(textBuffer_backup));

		//ImGui::SetNextItemWidth(-1); ImGui::Text(u8"生产地址:");
		//ImGui::SameLine();
		//ImGui::SetNextItemWidth(-1); ImGui::Text(u8"德州临邑睿阳纱网厂");

		//ImGui::SetNextItemWidth(-1); ImGui::Text(u8"联系电话:");
		//ImGui::SameLine();
		//ImGui::SetNextItemWidth(-1); ImGui::InputText("##ph", textBuffer_phone, IM_ARRAYSIZE(textBuffer_phone));

		//ImGui::NewLine();
		//// 如果按钮被按下
		////ImGui::SetNextItemWidth(-1);//Export to XLSX
		//if (ImGui::Button(u8"导出表格", ImVec2(-1, 0)))
		//{
		//	// 打开文件对话框，设置对话框的键名、标题、文件过滤器和初始目录
		//	ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save File", ".xlsx");
		//}

		//// 显示文件对话框并处理选择结果
		//if (ImGuiFileDialog::Instance()->Display("SaveFileDlgKey"))
		//{
		//	// 如果用户选择了文件
		//	if (ImGuiFileDialog::Instance()->IsOk())
		//	{
		//		// 获取选择的文件路径
		//		std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
		//		// 执行保存操作...
		//	}
		//	// 关闭文件对话框
		//	ImGuiFileDialog::Instance()->Close();
		//}
	}

	// 结束 ImGui 渲染
	ImGui::End();

}

void WishSoftware::draw_product_style_table()
{

	ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_FirstUseEver);
	ImGui::Begin(u8"产品类型设置窗口", &show_product_setting_window);
	if (ImGui::BeginTable("##Table", 9, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable))
	{
		ImGui::TableSetupColumn(u8"产品选择");
		ImGui::TableSetupColumn(u8"产品编号");
		ImGui::TableSetupColumn(u8"框宽v");
		ImGui::TableSetupColumn(u8"框高v");
		ImGui::TableSetupColumn(u8"扇宽v");
		ImGui::TableSetupColumn(u8"扇高v");
		ImGui::TableSetupColumn(u8"网宽v");
		ImGui::TableSetupColumn(u8"网高v");
		ImGui::TableSetupColumn(u8"价 格");
		ImGui::TableHeadersRow();
		for (int i = 0; i < product_rows.size(); i++)
		{
			ImGui::PushID(i); // 为每行创建一个唯一的ID

			ImGui::TableNextRow();
			// 添加Checkbox
			ImGui::TableSetColumnIndex(0);
			//ImGui::RadioButton((u8"产品" + std::to_string(i + 1)).c_str(), &product_rows[i].checked)
			//ImGui::RadioButton((u8"产品" + std::to_string(i + 1)).c_str(), &product_rows[i].checked);

			ImGui::RadioButton((u8"产品" + std::to_string(i + 1)).c_str(), &selection, i);
			

			//ImGui::SameLine;
			//ImGui::InputInt("##", &product_rows[i].p_id, 0, 0);
			//ImGui::InputText("##", const_cast<char*>(product_rows[i].p_id).data(),sizeof((product_rows[i].p_id).c_str()));
			ImGui::TableSetColumnIndex(1);
			ImGui::PushItemWidth(-1);
			ImGui::InputInt("##", &product_rows[i].p_id, 0, 0);
			for (int j = 0; j < 7; j++) {
				ImGui::TableSetColumnIndex(j+2);
				//ImGui::SameLine(); // 保持在同一行
				//ImGui::NextColumn(); // 移动到下一列
				//ImGui::SetNextItemWidth(-FLT_MIN); // 设置输入框宽度自适应
				//ImGui::SetNextItemWidth(item_width); // 设置每个输入框的宽度
				ImGui::PushItemWidth(-1);
				ImGui::InputInt(("##" + std::to_string(j + 1)).c_str(), &product_rows[i].data[j], 0, 0);
				//ImGui::InputInt(NULL, &product_rows[i].data[j], 0, 0);
			}

			ImGui::PopID();

		}
		ImGui::EndTable();
	}
	// 添加和减少行的按钮
	if (ImGui::Button(u8"添加产品类型")) {

		product_rows.push_back({ false, 112233, {0, 0, 0, 0, 0, 0,0} });
			
		//current_product_row++; // 增加行数
	}
	ImGui::SameLine();
	if (product_rows.size() > 0 && ImGui::Button(u8"减少产品类型")) {
		product_rows.pop_back(); // 删除最后一行;
	}
	ImGui::NewLine();
	if (ImGui::Button((u8"保存"), ImVec2(-1, 0)))
	{
		///write_priceCSV(m_priceData_fileName, price_data);
		write_productXML();
	}
	ImGui::End();


}
void WishSoftware::hideTabBar()
{
	ImGuiWindowClass window_class;
	window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
	ImGui::SetNextWindowClass(&window_class);
}

void WishSoftware::draw_table()
{
	hideTabBar();
	ImGui::Begin("Data Table"); // 创建一个窗口

	// 创建一个表格
	if (ImGui::BeginTable("##Table", 12, 
		ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable)) {

		// 表头
		ImGui::TableSetupColumn(u8"序号");
		ImGui::TableSetupColumn(u8"内径宽");
		ImGui::TableSetupColumn(u8"内径高");
		ImGui::TableSetupColumn(u8"数量");
		ImGui::TableSetupColumn(u8"框宽");
		ImGui::TableSetupColumn(u8"框高");
		//ImGui::TableSetupColumn(u8"数量");
		ImGui::TableSetupColumn(u8"扇宽");
		ImGui::TableSetupColumn(u8"扇高");
		//ImGui::TableSetupColumn(u8"数量");
		ImGui::TableSetupColumn(u8"网宽");
		ImGui::TableSetupColumn(u8"网高");
		//ImGui::TableSetupColumn(u8"数量");
		ImGui::TableSetupColumn(u8"单价");
		ImGui::TableSetupColumn(u8"金额");
		ImGui::TableHeadersRow();

		//int priceW = 0;
		//bool mask = false;
		for (int row = 0; row < tableData.size(); row++) {
			ImGui::PushID(row);
			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0);
			ImGui::Text("%d", tableData[row].serial_number);

			ImGui::TableSetColumnIndex(1);
			ImGui::PushItemWidth(-1);
			//ImGui::InputFloat("##inW", &tableData[row].inner_width, 0, 0, "%.2f");
			ImGui::InputInt("##inW", &tableData[row].inner_width, 0, 0);
			ImGui::TableSetColumnIndex(2);
			ImGui::PushItemWidth(-1);
			ImGui::InputInt("##inH", &tableData[row].inner_height, 0, 0);

			ImGui::TableSetColumnIndex(3);
			ImGui::PushItemWidth(-1);
			ImGui::InputInt("##q", &tableData[row].quantity, 0, 0);

			ImGui::TableSetColumnIndex(4);
			if (tableData[row].frame_width>frame_width_threshold)
			{
				ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(255, 0, 0, 255));
				//mask = true;
			}
			tableData[row].frame_width = tableData[row].inner_width + door_window.frame_width_vary;
			ImGui::Text("%d", tableData[row].frame_width);

			ImGui::TableSetColumnIndex(5);
			if (tableData[row].frame_height > frame_height_thmax || tableData[row].frame_height < frame_height_thmin)
			{
				ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(255, 0, 0, 255));
				//mask = true;
			}
			else
			{
				// 恢复原色（透明）
				ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0));
			}
			tableData[row].frame_height = tableData[row].inner_height + door_window.frame_height_vary;
			ImGui::Text("%d", tableData[row].frame_height);

			//ImGui::TableSetColumnIndex(6);
			//tableData[row].quantity_frame = tableData[row].quantity; // 第七列数据和第四列保持一致
			//ImGui::Text("%d", tableData[row].quantity_frame);
			//ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)); // 黄色文本
			//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.0f, 1.0f, 0.0f, 0.25f)); // 黄色背景，半透明
			ImGui::TableSetColumnIndex(6);
			//ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(255, 255, 0, 255)); // 设置为黄色
			tableData[row].fan_width = tableData[row].inner_width + door_window.fan_width_vary;
			ImGui::Text("%d", tableData[row].fan_width);
			//ImGui::PopStyleColor(2); // 恢复默认颜色

			ImGui::TableSetColumnIndex(7);
			tableData[row].fan_height = tableData[row].inner_height + door_window.fan_height_vary;
			ImGui::Text("%d", tableData[row].fan_height);

			//ImGui::TableSetColumnIndex(9);
			//tableData[row].quantity_fan = tableData[row].quantity; // 第七列数据和第四列保持一致
			//ImGui::Text("%d", tableData[row].quantity_fan);

			ImGui::TableSetColumnIndex(8);
			tableData[row].net_width = tableData[row].inner_width + door_window.net_width_vary;
			ImGui::Text("%d", tableData[row].net_width);

			ImGui::TableSetColumnIndex(9);
			tableData[row].net_height = tableData[row].inner_height + door_window.net_height_vary;
			ImGui::Text("%d", tableData[row].net_height);

			//ImGui::TableSetColumnIndex(12);
			//tableData[row].quantity_net = tableData[row].quantity; // 第七列数据和第四列保持一致
			//ImGui::Text("%d", tableData[row].quantity_net);

			ImGui::TableSetColumnIndex(10);
			if (tableData[row].frame_width > frame_width_threshold ||
				tableData[row].frame_height > frame_height_thmax ||
				tableData[row].frame_height < frame_height_thmin)
			{
				ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 255, 0, 255));
			}
			else
			{
				// 恢复原色（透明）
				ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0));

			}

			ImGui::PushItemWidth(-1);
			//tableData[row].quantity_net = tableData[row].quantity; // 第七列数据和第四列保持一致
			ImGui::InputInt("##p", &tableData[row].price, 0, 0);
			//ImGui::InputInt("##p", &price_mask, 0, 0);


			ImGui::TableSetColumnIndex(11);
			//tableData[row].quantity_net = tableData[row].quantity; // 第七列数据和第四列保持一致
			ImGui::Text("%d", tableData[row].price*(tableData[row].quantity));

			//priceW = tableData[row].price * (tableData[row].quantity) + priceW;

			ImGui::PopID();
		}
		if (tableData.size()>0)
		{
			// 添加新的一行，合并前11列
			ImGui::TableNextRow();
			ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(0, 199, 128, 140));
			ImGui::TableSetColumnIndex(2); // 移动到第3列
			ImGui::Text(u8"总数量:");
			ImGui::TableSetColumnIndex(3); // 移动到第11列
			ImGui::Text("%d", num_whole);
			ImGui::TableSetColumnIndex(6); // 移动到第11列
			ImGui::Text(u8"应收金额:");
			ImGui::TableSetColumnIndex(7); // 移动到第11列
			ImGui::Text("%d", price_whole_);
			//ImGui::TableMergeCells(0, 11, true); // 合并从第0列到第11列的单元格
			ImGui::TableSetColumnIndex(10); // 移动到第11列
			ImGui::Text(u8"实收金额:"); // 在合并的单元格中显示文本
			ImGui::TableSetColumnIndex(11); // 移动到第11列
			ImGui::Text("%d", price_whole);
		}

		ImGui::EndTable();
	}

	// 增加行的按钮
	//if (ImGui::Button("Add Row")) {
	//	if (currentRowCount < 100) { // 防止超出数组界限
	//		int newRow = currentRowCount;
	//		tableData[newRow].serial_number = newRow + 1; // 序号从1开始自然增加
	//		tableData[newRow].inner_width = 0;
	//		tableData[newRow].inner_height = 0;
	//		tableData[newRow].quantity = 0;
	//		tableData[newRow].frame_width = 0;
	//		tableData[newRow].frame_height = 0;
	//		tableData[newRow].quantity_frame = 0;
	//		tableData[newRow].fan_width = 0;
	//		tableData[newRow].fan_height = 0;
	//		tableData[newRow].quantity_fan = 0;
	//		tableData[newRow].net_width = 0;
	//		tableData[newRow].net_height = 0;
	//		tableData[newRow].quantity_net = 0;
	//		currentRowCount++;
	//	}
	//}
	if (ImGui::Button(u8"增加行"))
	{
		currentRowCount++;
		tableData.push_back({ currentRowCount,0,0,0,0,0,0,0,0,0,0 });
	}
	ImGui::SameLine();

	// 减少行的按钮
	//if (ImGui::Button("Remove Row")) {
	//	if (currentRowCount > 0) {
	//		currentRowCount--;
	//	}
	//}
	if (tableData.size() > 0 && ImGui::Button(u8"减少行")) {
		tableData.pop_back(); // 删除最后一行;
	}
	
	ImGui::End();
}

void WishSoftware::draw_menu()
{
	//ImGui::Begin("main window", &show_main_window, ImGuiWindowFlags_MenuBar);
	// 菜单栏
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu(u8"文件")) {

			if (ImGui::MenuItem(u8"制作表单")) {
				// 处理导出生产单的逻辑
				show_product_xlsx = true;

			}
			if (ImGui::MenuItem(u8"加载表单")) {
				// 处理导出随货单的逻辑
				show_sale_xlsx = true;
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu(u8"产品类型")) {
			 //产品类型设置窗口
			show_product_setting_window = true;
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu(u8"参数设置")) {
			//if (ImGui::MenuItem(u8"打开价格表")) {
			//	// 处理打开价格表的逻辑
			//}
			//if (ImGui::MenuItem(u8"加载价格表")) {
			//	// 处理加载价格表的逻辑
			//}
			show_param_setting_window = true;
			ImGui::EndMenu();
		}



		//增加主题切换
		if (ImGui::BeginMenu(u8"主题（Other）"))
		{
			if (ImGui::MenuItem(u8"暗黑（Dark）")) { ImGui::StyleColorsDark(); }
			if (ImGui::MenuItem(u8"明亮（Light）")) { ImGui::StyleColorsLight(); }
			if (ImGui::MenuItem(u8"经典（Classic）")) { ImGui::StyleColorsClassic(); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu(u8"软件说明")) {
			ImGui::Text(u8"关注 ->   微信公众号  RobotH ");
			ImGui::Text(u8"联系邮箱: Given666888@163.com");
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

}
void WishSoftware::draw_product_style_window()
{
	ImGui::Begin(u8"产品类型设置窗口", &show_product_setting_window);
	// 设置窗口的内容
	//ImGui::Text(u8"这里是产品类型的设置内容");
	// 创建多列布局
	//ImGui::Columns(7, "productData", false); // 7列，列宽自适应
	ImGui::SetNextItemWidth(-1); ImGui::Text(u8"产品类型"); ImGui::SameLine();
	ImGui::SetNextItemWidth(-1); ImGui::Text(u8"框宽变化"); ImGui::SameLine();
	ImGui::SetNextItemWidth(-1); ImGui::Text(u8"框高变化"); ImGui::SameLine();
	ImGui::SetNextItemWidth(-1); ImGui::Text(u8"扇宽变化"); ImGui::SameLine();
	ImGui::SetNextItemWidth(-1); ImGui::Text(u8"扇高变化"); ImGui::SameLine();
	ImGui::SetNextItemWidth(-1); ImGui::Text(u8"网宽变化"); ImGui::SameLine();
	ImGui::SetNextItemWidth(-1); ImGui::Text(u8"网高变化"); 
	//ImGui::NextColumn();
	ImGui::Separator(); // 每行结束后添加分隔线
	for (int i = 0; i < product_rows.size(); i++) {
		ImGui::PushID(i); // 为每行创建一个唯一的ID

		// 添加Checkbox
		ImGui::Checkbox((u8"产品" + std::to_string(i + 1)).c_str(), &product_rows[i].checked);

		// 添加6个整型输入框
		float window_width = ImGui::GetWindowWidth();
		// 假设窗口宽度足够，将宽度平均分配给7个控件（1个Checkbox和6个输入框）
		float item_width = window_width / 7.0f; 
		for (int j = 0; j < 6; j++) {
			ImGui::SameLine(); // 保持在同一行
			//ImGui::NextColumn(); // 移动到下一列
			//ImGui::SetNextItemWidth(-FLT_MIN); // 设置输入框宽度自适应
			ImGui::SetNextItemWidth(item_width); // 设置每个输入框的宽度
			ImGui::InputInt(("##data" + std::to_string(j + 1)).c_str(), &product_rows[i].data[j], 0, 0);
		}

		ImGui::PopID();
		ImGui::Separator(); // 每行结束后添加分隔线
	}
	// 添加和减少行的按钮
	if (ImGui::Button("add product style")) {
		product_rows.push_back({ false,1112233, {0, 0, 0, 0, 0, 0} });
		//current_product_row++; // 增加行数
	}
	ImGui::SameLine();
	if (product_rows.size() > 0 && ImGui::Button("remove product style")) {
		product_rows.pop_back(); // 删除最后一行;
	}
	ImGui::End();



}
int WishSoftware::show_window()
{
	init_priceData();
	read_productXML();
	read_paramSetting();
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		return 1;
	}

	// Use GL 3.2 (All Platforms)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// 设置窗口和OpenGL上下文
	// 创建隐藏的GLFW窗口
	//glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // 隐藏窗口
	GLFWwindow* window = glfwCreateWindow(1280, 720, u8"德州睿阳纱网厂专用软件", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // 开启垂直同步

	// Initialize OpenGL loader
	if (gl3wInit() != 0) {
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// 设置ImGui上下文
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsLight();
	ImFont* myFont = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 18.0f,
		NULL, io.Fonts->GetGlyphRangesChineseFull());


	// 获取ImGui的样式引用
	//ImGuiStyle& style = ImGui::GetStyle();

	// 设置窗口背景颜色为白色，颜色值的格式是0到1之间的浮点数
	//style.Colors[ImGuiCol_WindowBg] = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); // 

	// 初始化ImGui平台和渲染器绑定
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	show_main_window = true;
	show_product_setting_window = false;
	// 主循环
	while (!glfwWindowShouldClose(window))
	{
		// 处理输入
		glfwPollEvents();

		update_door_window_vary();
		update_price_new();
		get_current_time();

		// 开始ImGui帧
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;  
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		{
			//draw_menu();
			ImGui::Begin("main window",nullptr, window_flags);
			if (opt_fullscreen)
				ImGui::PopStyleVar(2);    // Submit the DockSpace
			ImGuiIO& io = ImGui::GetIO();

			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			draw_menu();
			// 创建停靠空间
			//ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			//ImGui::DockSpace(dockspace_id);
			// 绘制表格

			if (show_product_setting_window)
			{	
				//ImGui::Begin(u8"产品类型设置窗口", &show_product_setting_window);
				//// 设置窗口的内容
				//ImGui::Text(u8"这里是产品类型的设置内容");
				//ImGui::End();
				draw_product_style_table();
			}
			if (show_param_setting_window)
			{
				//draw_price_style_table();
				draw_param_setting_window();
			}
			
			if (show_product_xlsx)
			{
				draw_product_xlxs_window();
			}
			//ImGui::SetNextWindowSize(ImVec2(720, 360), ImGuiCond_FirstUseEver);
			//if (show_sale_xlsx)
			//{
			//	draw_sale_xlxs_window();
			//}

			//ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
			draw_table();
			//update_door_window_vary();
			//update_price();
			
		}
		ImGui::End();

		// 渲染ImGui帧
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}

	// 清理资源
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
void WishSoftware::init_priceData()
{
	price_data = read_priceCSV(m_priceData_fileName);
}
std::vector<std::vector<int>> WishSoftware::read_priceCSV(const std::string& filename)
{
	std::vector<std::vector<int>> data;
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return data;
	}

	while (std::getline(file, line)) {
		std::vector<int> row;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ',')) {
			row.push_back(std::stoi(cell));
		}
		data.push_back(row);
	}

	return data;

}

void WishSoftware::write_priceCSV(const std::string& filename, const std::vector<std::vector<int>>& data)
{
	std::ofstream file(filename, std::ios::out);
	//std::cout << data.size() << std::endl;
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	for (const auto& row : data) {
		for (size_t i = 0; i < row.size(); ++i) {
			file << row[i];
			if (i < row.size() - 1) file << ",";
		}
		file << "\n";
	}
}
void WishSoftware::read_productXML()
{
	// 读取XML文件
	pugi::xml_document loaded_doc;
	pugi::xml_parse_result result = loaded_doc.load_file(m_productData_fileName.c_str());
	if (!result) {
		std::cerr << "Failed to load XML file: " << result.description() << std::endl;
		return ;
	}

	// 读取并打印XML文件的内容
	//std::cout << "Reading XML file contents:" << std::endl;
	int index = 0;
	for (pugi::xml_node node : loaded_doc.child("root").children("node")) {
		//std::cout << "Node ID: " << node.attribute("id").as_string() << std::endl;
		ProductRow product_row;
		product_row.p_id = node.attribute("id").as_int();
		product_row.checked= node.child("checked").text().as_bool();
		if (product_row.checked)
		{
			selection = index;
		}
		//std::cout << product_row.checked << std::endl;
		//product_rows[index].p_id = std::stoi(pid);
		for (pugi::xml_node data : node.children("data")) {
			//std::cout << "  Data: " << data.text().as_int() << std::endl;
			product_row.data.push_back(data.text().as_int());
		}
		//product_row.checked = false;
		product_rows.push_back(product_row);
		index++;
	}
}
void WishSoftware::write_productXML()
{
	// 创建一个新的XML文档
	pugi::xml_document doc;
	// 创建根节点
	pugi::xml_node root = doc.append_child("root");

	// 清除现有的节点
	root.remove_children();

	// 假设我们有6个节点，每个节点ID分别为ID1至ID6，每个节点包含6个整型数据
	//std::vector<std::string> node_ids = { "ID8", "ID100", "ID3", "ID4", "ID5", "ID6" };
	//int data_for_each_node[6][6] = {
	//	{1, 2, 10, 4, 5, 6},
	//	{7, 8, 12, 10, 11, 12},
	//	{13, 14, 15, 16, 17, 18},
	//	{19, 20, 21, 22, 23, 24},
	//	{25, 26, 27, 28, 29, 30},
	//	{31, 32, 33, 34, 35, 36}
	//};
	
	int index = 0;
	// 为每个节点创建XML节点并添加数据
	for (auto &product:product_rows) {
		// 创建节点并设置ID属性
		pugi::xml_node node = root.append_child("node");
		//node.append_attribute("id") =  node_ids[i].c_str();
		node.append_attribute("id") = std::to_string(product.p_id).c_str();
		pugi::xml_node data_node = node.append_child("checked");
		if (index==selection)
		{
			data_node.text().set("true");
		}
		else
		{
			data_node.text().set("false");
		}
		// 为节点添加6个整型数据
		for (int j = 0; j < product.data.size(); ++j) {
			pugi::xml_node data_node = node.append_child("data");
			char buffer[32];
			sprintf_s(buffer, "%d", product.data[j]); // 将整数转换为字符串
			data_node.text().set(buffer); // 设置文本节点的值
		}
		index++;
	}

	// 保存XML文件
	bool save_success = doc.save_file(m_productData_fileName.c_str());
	if (!save_success) {
		std::cerr << "Failed to save XML file." << std::endl;
		return ;
	}

	std::cout << "XML file has been written successfully." << std::endl;
}

void WishSoftware::update_door_window_vary()
{
	if (selection==-1)
	{
		door_window.frame_width_vary = 0;
		door_window.frame_height_vary = 0;
		door_window.fan_width_vary = 0;
		door_window.fan_height_vary = 0;
		door_window.net_width_vary = 0;
		door_window.net_height_vary = 0;
	}
	else if (& product_rows[selection].data[0] == NULL)
	{
		selection = -1;
	}
	else
	{
		door_window.frame_width_vary = product_rows[selection].data[0];
		door_window.frame_height_vary = product_rows[selection].data[1];
		door_window.fan_width_vary = product_rows[selection].data[2];
		door_window.fan_height_vary = product_rows[selection].data[3];
		door_window.net_width_vary = product_rows[selection].data[4];
		door_window.net_height_vary = product_rows[selection].data[5];
	}

}
void WishSoftware::update_price_new()
{
	int priceW = 0,priceW_ = 0;
	int index = 0;
	int num = 0;
	int price_mask = 0;
	for (auto& table_data : tableData)
	{
		
		if (table_data.frame_width < frame_width_threshold &&  ( table_data.frame_height >= frame_height_thmin && table_data.fan_height<=frame_height_thmax))
		{
			//ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(255, 255, 0, 255)); // 设置为黄
			table_data.price = product_rows[selection].data.back();
		}
		//if (table_data.price!= product_rows[selection].data.back())
		//{
		//	price_mask = table_data.price;
		//}
		//index++;
		num = num + table_data.quantity;
		priceW = priceW + table_data.price * table_data.quantity;
		priceW_ = priceW_ + product_rows[selection].data.back() * table_data.quantity;
	}
	price_whole = priceW;
	price_whole_ = priceW_;
	num_whole = num;
}

void WishSoftware::update_price()
{
	int priceW = 0;
	int index = 0;
	for (auto &table_data : tableData)
	{
		for (const auto &price:price_data)
		{
			if ((table_data.frame_width>price[0]) && (table_data.frame_width<price[1]) &&
				(table_data.frame_height>price[2])&&(table_data.frame_height<price[3]))
			{
				//tableData[index].price = price[4];
				table_data.price = price[4];
			}
			else
			{
				index++;
			}
			//else
			//{
			//	tableData[index].price = 100;
			//	//table_data.price = 100;
			//}
		}
		if (index== price_data.size())
		{
			table_data.price = 0;
		}
		//index++;
		priceW = priceW + table_data.price * table_data.quantity;
	}
	price_whole = priceW;
}

void WishSoftware::get_current_time()
{
	// Get current time
	auto now = std::chrono::system_clock::now();
	auto now_c = std::chrono::system_clock::to_time_t(now);
	std::stringstream ss,ss1;
	ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d");
	ss1 << std::put_time(std::localtime(&now_c), "%Y%m%d%H%M");
	current_date = ss.str();
	order_numer = ss1.str();
}
void WishSoftware::create_xlsx()
{
	workbook = workbook_new(xlsx_file_name.c_str());
	init_format_xlsx();
	create_product_xlsx();
	create_sale_xlsx();
	// 关闭工作簿。
	workbook_close(workbook);

}

void WishSoftware::create_sale_xlsx()
{
	int col_num = 8;

	worksheet2 = workbook_add_worksheet(workbook, "随货单");

	// 设置列宽，总和为230mm，这里假设每个列宽单位为1.7mm（Excel中默认的列宽单位）。
	double column_width = sale_table.length / col_num;
	for (int col = 0; col < 13; ++col) {
		worksheet_set_column(worksheet2, col, col, column_width / 2.54, NULL);
	}

	// 设置第一行表格高度。
	worksheet_set_row(worksheet2, 0, sale_table.row1, NULL);
	// 设置第一行的单元格合并。
	worksheet_merge_range(worksheet2, 0, 0, 0, col_num - 1, textBuffer_name2, format_topic);



	// 设置第二行&第三行表格高度。
	worksheet_set_row(worksheet2, 1, sale_table.row2, NULL);
	worksheet_set_row(worksheet2, 2, sale_table.row3, NULL);

	std::string str_customer = "客户: ";
	worksheet_merge_range(worksheet2, 1, 0, 1, col_num - 7, (str_customer + textBuffer_custmor).c_str(), format_info);
	//worksheet_write_string(worksheet, 1, 4, "日期:", NULL); 
	std::string str_customer_p = "电话: ";
	worksheet_merge_range(worksheet2, 1, col_num - 6, 1, col_num - 4, (str_customer_p + textBuffer_custmor_phone).c_str(), format_info);
	//worksheet_write_string(worksheet, 1, 7, "备注:", NULL);
	worksheet_merge_range(worksheet2, 1, col_num - 3, 1, col_num - 1, ("订单编号: " + order_numer).c_str(), format_info);

	std::string str_address = "地址: ";
	worksheet_merge_range(worksheet2, 2, 0, 2, col_num - 4, (str_address + textBuffer_custmor_address).c_str(), format_info);
	//std::string str_color = "颜色: ";
	//worksheet_merge_range(worksheet2, 2, col_num - 7, 2, col_num - 5, (str_color + textBuffer_color).c_str(), format_info);
	std::string str_color = "颜色: ";
	worksheet_merge_range(worksheet2, 2, col_num - 3, 2, col_num - 1, (str_color + textBuffer_color).c_str(), format_info);

	// 设置第四行表格高度。
	worksheet_set_row(worksheet2, 3, sale_table.row4, NULL);
	std::vector<std::string> headers = {
		 "序 号", "内径-宽*高", "数 量", "框-宽*高", "扇-宽*高", "网-宽*高","单 价", "总 价"
	};
	int index = 0;
	for (const auto& header : headers)
	{
		worksheet_write_string(worksheet2, 3, index, headers[index].c_str(), format_table);
		index++;
	}

	//int price_ = 0;
	//输入内容
	for (size_t i = 0; i < tableData.size(); i++)
	{
		worksheet_set_row(worksheet2, i+4 , sale_table.data_row, NULL);
		worksheet_write_string(worksheet2, i + 4, 0, std::to_string(tableData[i].serial_number).c_str(), format_table);
		std::string inner = std::to_string(tableData[i].inner_width) + "*" + std::to_string(tableData[i].inner_height);
		worksheet_write_string(worksheet2, i + 4, 1, inner.c_str(), format_table);
		//worksheet_write_string(worksheet1, i + 4, 2, std::to_string(tableData[i].inner_height).c_str(), format_table);
		worksheet_write_string(worksheet2, i + 4, 2, std::to_string(tableData[i].quantity).c_str(), format_table);

		std::string frame = std::to_string(tableData[i].frame_width) + "*" + std::to_string(tableData[i].frame_height);
		worksheet_write_string(worksheet2, i + 4, 3, frame.c_str(), format_table);
		//worksheet_write_string(worksheet1, i + 4, 5, std::to_string(tableData[i].frame_height).c_str(), format_table);
		//worksheet_write_string(worksheet1, i + 4, 6, std::to_string(tableData[i].quantity_frame).c_str(), format_table);
		std::string fan = std::to_string(tableData[i].fan_width) + "*" + std::to_string(tableData[i].fan_height);
		worksheet_write_string(worksheet2, i + 4, 4, fan.c_str(), format_table);
		//worksheet_write_string(worksheet1, i + 4, 7, std::to_string(tableData[i].fan_height).c_str(), format_table);
		//worksheet_write_string(worksheet1, i + 4, 9, std::to_string(tableData[i].quantity_fan).c_str(), format_table);
		std::string net = std::to_string(tableData[i].net_width) + "*" + std::to_string(tableData[i].net_width);
		worksheet_write_string(worksheet2, i + 4, 5, net.c_str(), format_table);

		//if (tableData[i].price != product_rows[selection].data.back())
		//{
		//	std::string str_ = " [惠]";
		//	worksheet_write_string(worksheet2, i + 4, 6, (std::to_string(tableData[i].price)+ str_).c_str(), format_table);
		//}
		//else
		//{
		worksheet_write_string(worksheet2, i + 4, 6, std::to_string(tableData[i].price).c_str(), format_table);
		
		int priceW = tableData[i].price * tableData[i].quantity;
		worksheet_write_string(worksheet2, i + 4, 7, std::to_string(priceW).c_str(), format_table);

		//price_ = price_ + priceW;
		//worksheet_write_string(worksheet1, i + 4, 12, std::to_string(tableData[i].quantity_net).c_str(), format_table);

	}

	//std::string str_color = "颜色: ";
	int current_row = tableData.size() + 4;
	worksheet_set_row(worksheet2, current_row, sale_table.row5_6, NULL);
	std::string str_f = u8"应收合计:  ";
	std::string price_wf = u8"￥" + std::to_string(price_whole_);
	worksheet_merge_range(worksheet2, current_row, 0, current_row, col_num - 5, (str_f + price_wf).c_str(), format_table);
	std::string str_r = u8"实收合计:  ";
	std::string price_w = u8"￥" + std::to_string(price_whole);
	worksheet_merge_range(worksheet2, current_row, col_num - 4, current_row, col_num - 1, (str_r+price_w).c_str(), format_table);


	worksheet_set_row(worksheet2, current_row + 1, sale_table.row5_6, NULL);
	worksheet_merge_range(worksheet2, current_row + 1, 0, current_row + 1, col_num - 5, u8"人民币金额大写: ", format_table);
	std::string money = numberToChinese(price_whole) + u8"元";
	worksheet_merge_range(worksheet2, current_row + 1, col_num - 4, current_row + 1, col_num - 1, money.c_str(), format_table);

	worksheet_set_row(worksheet2, current_row + 2, sale_table.row7, NULL);
	worksheet_set_row(worksheet2, current_row + 3, sale_table.row7, NULL);
	std::string str_paddress = u8"生产地址: ";
	worksheet_merge_range(worksheet2, current_row + 3, 0, current_row + 2, col_num - 1,(str_paddress+ textBuffer_address).c_str(), format_info);

	worksheet_set_row(worksheet2, current_row + 4, sale_table.row8, NULL);
	std::string str_phone = u8"联系电话: ";
	worksheet_merge_range(worksheet2, current_row + 4, 0, current_row + 4, col_num - 5, (str_phone + textBuffer_phone).c_str(), format_info);
	//std::string str_date = u8"发货日期:";
	worksheet_merge_range(worksheet2, current_row + 4, col_num - 3, current_row + 4, col_num - 1, u8"发货日期: ", format_info);


}

void WishSoftware::create_product_xlsx()
{
	int col_num = 16;

	worksheet1 = workbook_add_worksheet(workbook, "生产单");

	// 设置列宽，总和为230mm，这里假设每个列宽单位为1.7mm（Excel中默认的列宽单位）。
	double column_width = 200.0 / (col_num-3);
	for (int col = 0; col < col_num ; ++col) {
		if (col==4||col==8||col==12)
		{
			worksheet_set_column(worksheet1, col, col, 2.0 / 2.54, NULL);
		}
		else
		{
			worksheet_set_column(worksheet1, col, col, column_width / 2.54, NULL);
		}
	}

	// 设置第一行的单元格合并。
	worksheet_merge_range(worksheet1, 0, 0, 0, col_num-1, textBuffer_name, format_topic);

	// 设置第一行表格高度。
	worksheet_set_row(worksheet1, 0, product_table.row1, NULL);

	// 设置第二行&第三行表格高度。
	worksheet_set_row(worksheet1, 1, product_table.row2, NULL);
	worksheet_set_row(worksheet1, 2, product_table.row3, NULL);
	// 合并第二行的单元格，并设置内容。
	//worksheet_write_string(worksheet, 1, 0, "客户:", NULL);
	std::string str_customer = "客户: ";
	worksheet_merge_range(worksheet1, 1, 0, 1, col_num-12, (str_customer+textBuffer_custmor).c_str(), format_info);
	//worksheet_write_string(worksheet, 1, 4, "日期:", NULL);
	worksheet_merge_range(worksheet1, 1, col_num-11, 1, col_num-6, ("日期: "+current_date).c_str(), format_info);
	//worksheet_write_string(worksheet, 1, 7, "备注:", NULL);
	worksheet_merge_range(worksheet1, 1,col_num-5, 1, col_num-1, ("订单编号:"+order_numer).c_str(), format_info);

	std::string str_psty = "产品类型: " + std::to_string(product_rows[selection].p_id);
	worksheet_merge_range(worksheet1, 2, 0, 2, col_num - 12, str_psty.c_str(), format_info);
	std::string str_color = "颜色: ";
	worksheet_merge_range(worksheet1, 2, col_num-11, 2, col_num - 6, (str_color + textBuffer_color).c_str(), format_info);
	std::string str_backup = "备注: ";
	worksheet_merge_range(worksheet1, 2, col_num-5, 2, col_num-1, (str_backup + textBuffer_backup).c_str(), format_info);

	// 设置第四行表格高度。
	worksheet_set_row(worksheet1, 3, product_table.row4, NULL);
	std::vector<std::string> headers = {
		 "序号", "内径宽", "内径高", "数量", "框宽", "框高","数量",
		"扇宽", "扇高","数量", "网宽", "网高","数量"
	};
	int index = 0;
	std::vector<int> index_col = { 0,1,2,3,5,6,7,9,10,11,13,14,15 };
	for (const auto& header : headers)
	{

	    worksheet_write_string(worksheet1, 3, index_col[index], headers[index].c_str(), format_table);

		index++;
	}
	worksheet_write_string(worksheet1, 3, 4, NULL, format_table);
	worksheet_write_string(worksheet1, 3, 8, NULL, format_table);
	worksheet_write_string(worksheet1, 3, 12, NULL, format_table);

	//输入内容
	for (size_t i = 0; i < tableData.size(); i++)
	{
		worksheet_set_row(worksheet1, i + 4, product_table.data_row, NULL);
		worksheet_write_string(worksheet1, i + 4, 0, std::to_string(tableData[i].serial_number).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 1, std::to_string(tableData[i].inner_width).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 2, std::to_string(tableData[i].inner_height).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 3, std::to_string(tableData[i].quantity).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 4, NULL, format_table);
		worksheet_write_string(worksheet1, i + 4, 5, std::to_string(tableData[i].frame_width).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 6, std::to_string(tableData[i].frame_height).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 7, std::to_string(tableData[i].quantity).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 8, NULL, format_table);
		worksheet_write_string(worksheet1, i + 4, 9, std::to_string(tableData[i].fan_width).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 10, std::to_string(tableData[i].fan_height).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 11, std::to_string(tableData[i].quantity).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 12, NULL, format_table);
		worksheet_write_string(worksheet1, i + 4, 13, std::to_string(tableData[i].net_width).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 14, std::to_string(tableData[i].net_height).c_str(), format_table);
		worksheet_write_string(worksheet1, i + 4, 15, std::to_string(tableData[i].quantity).c_str(), format_table);
		
	}
	worksheet_merge_range(worksheet1, 3, 4, 4 + tableData.size(), 4, NULL,NULL);
	worksheet_merge_range(worksheet1, 3, 8, 4 + tableData.size(), 8, NULL, NULL);
	worksheet_merge_range(worksheet1, 3, 12, 4 + tableData.size(), 12, NULL, NULL);

}


void WishSoftware::init_format_xlsx()
{
	/***************题目格式****************/
	// 创建一个格式对象
	format_topic = workbook_add_format(workbook);
	// 设置字体为微软雅黑，支持中文显示
	format_set_font_name(format_topic, "宋体");
	// 设置字体大小
	format_set_font_size(format_topic, 16);
	// 设置字体颜色
	format_set_font_color(format_topic, 0x000000); // 黑色
	// 设置文本为粗体
	//format_set_bold(format);
	// 设置水平和垂直对齐方式为居中
	format_set_align(format_topic, LXW_ALIGN_CENTER);
	format_set_align(format_topic, LXW_ALIGN_VERTICAL_CENTER);

	/***************信息格式****************/
	format_info = workbook_add_format(workbook);
	// 设置字体为微软雅黑，支持中文显示
	format_set_font_name(format_info, "宋体");
	// 设置字体大小
	format_set_font_size(format_info, 11);
	// 设置字体颜色
	format_set_font_color(format_info, 0x000000); // 黑色
	// 设置文本为粗体
	//format_set_bold(format);
	// 设置水平和垂直对齐方式为居中
	format_set_align(format_info, LXW_ALIGN_LEFT);
	format_set_align(format_info, LXW_ALIGN_VERTICAL_CENTER);

	/******************表格内容部分*******************/
	format_table = workbook_add_format(workbook);
	format_set_border(format_table, LXW_BORDER_THIN); // 设置边框
	format_set_font_name(format_table, "宋体"); // 设置字体
	format_set_font_size(format_table, 11); // 设置字体大小
	//format_set_bold(table_format); // 设置粗体
	//format_set_text_wrap(header_format); // 设置文本换行
	format_set_align(format_table, LXW_ALIGN_CENTER); // 设置水平居中
	format_set_align(format_table, LXW_ALIGN_VERTICAL_CENTER); // 设置水平居中
}

std::string WishSoftware::numberToChinese(int number)
{
	std::vector<std::string> chineseNumbers = {
		"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"
	};
	std::vector<std::string> units = {
		"", "拾", "佰", "仟"
	};
	std::vector<std::string> bigUnits = {
		"", "万", "亿", "万亿"
	};
	std::string chinese;
	int unitIndex = 0;
	bool zero = false;

	if (number == 0) {
		return "零";
	}

	while (number > 0) {
		int part = number % 10000;
		if (part == 0) {
			if (!zero) {
				chinese = chineseNumbers[0] + chinese;
			}
			zero = true;
		}
		else {
			zero = false;
			int i = 0;
			bool partZero = true;
			while (part > 0) {
				int digit = part % 10;
				if (digit == 0) {
					if (!partZero) {
						chinese = chineseNumbers[digit] + chinese;
					}
				}
				else {
					partZero = false;
					chinese = chineseNumbers[digit] + units[i] + chinese;
				}
				part /= 10;
				i++;
			}
			if (!partZero) {
				chinese = bigUnits[unitIndex] + chinese;
			}
		}
		number /= 10000;
		unitIndex++;
	}

	return chinese;
}
std::string WishSoftware::formatCurrency(double amount)
{
	int integerPart = static_cast<int>(amount);
	double decimalPart = amount - integerPart;
	std::string chineseInteger = numberToChinese(integerPart);

	// Handle the decimal part
	std::string chineseDecimal;
	int jiao = static_cast<int>(decimalPart * 10);
	int fen = static_cast<int>(int(decimalPart * 100) % 10);

	if (jiao > 0) {
		chineseDecimal = numberToChinese(jiao) + "角";
	}
	if (fen > 0) {
		chineseDecimal += numberToChinese(fen) + "分";
	}
	// Remove the trailing "零" if exists
	size_t lastZeroPos = chineseInteger.rfind("零");
	if (lastZeroPos != std::string::npos) {
		chineseInteger.erase(lastZeroPos, 3);
	}

	return chineseInteger + "元" + chineseDecimal;
}

void WishSoftware::read_paramSetting()
{
	// first, create a file instance
	mINI::INIFile file("paramSetting.ini");
	// next, create a structure that will hold data
	mINI::INIStructure ini;
	// now we can read the file
	file.read(ini);
	// read a value
	//std::string width= ini["setting"]["width"];
	frame_width_threshold = std::stoi(ini["setting"]["width"]);
	frame_height_thmax = std::stoi(ini["setting"]["height_max"]);
	frame_height_thmin = std::stoi(ini["setting"]["height_min"]);

	product_table.row1 = std::stoi(ini["productTable"]["row1"]);
	product_table.row2 = std::stoi(ini["productTable"]["row2"]);
	product_table.row3 = std::stoi(ini["productTable"]["row3"]);
	product_table.row4 = std::stoi(ini["productTable"]["row4"]);
	product_table.data_row = std::stoi(ini["productTable"]["data_row"]);



	sale_table.length = std::stoi(ini["saleTable"]["length"]);
	sale_table.row1 = std::stoi(ini["saleTable"]["row1"]);
	sale_table.row2 = std::stoi(ini["saleTable"]["row2"]);
	sale_table.row3 = std::stoi(ini["saleTable"]["row3"]);
	sale_table.row4 = std::stoi(ini["saleTable"]["row4"]);
	sale_table.data_row = std::stoi(ini["saleTable"]["data_row"]);
	sale_table.row5_6 = std::stoi(ini["saleTable"]["row5_6"]);
	sale_table.row7 = std::stoi(ini["saleTable"]["row7"]);
	sale_table.row8 = std::stoi(ini["saleTable"]["row8"]);

}
void WishSoftware::write_paramSetting()
{
	// first, create a file instance
	mINI::INIFile file("paramSetting.ini");
	// next, create a structure that will hold data
	mINI::INIStructure ini;

	// now we can read the file
	file.read(ini);
	ini["setting"]["width"] = std::to_string(frame_width_threshold);
	ini["setting"]["height_max"] = std::to_string(frame_height_thmax);
	ini["setting"]["height_min"] = std::to_string(frame_height_thmin);

	ini["productTable"]["row1"] = std::to_string(product_table.row1);
	ini["productTable"]["row2"] = std::to_string(product_table.row2);
	ini["productTable"]["row3"] = std::to_string(product_table.row3);
	ini["productTable"]["row4"] = std::to_string(product_table.row4);
	ini["productTable"]["data_row"] = std::to_string(product_table.data_row);

	ini["saleTable"]["length"] = std::to_string(sale_table.length);
	ini["saleTable"]["row1"] = std::to_string(sale_table.row1);
	ini["saleTable"]["row2"] = std::to_string(sale_table.row2);
	ini["saleTable"]["row3"] = std::to_string(sale_table.row3);
	ini["saleTable"]["row4"] = std::to_string(sale_table.row4);
	ini["saleTable"]["data_row"] = std::to_string(sale_table.data_row);
	ini["saleTable"]["row5_6"]= std::to_string(sale_table.row5_6);
	ini["saleTable"]["row7"] = std::to_string(sale_table.row7);
	ini["saleTable"]["row8"] = std::to_string(sale_table.row8);

	// write updates to file
	file.write(ini);

}