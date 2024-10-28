#include <xlsxwriter.h>
#include <wchar.h>
#include <windows.h>
#include <iostream>
#include <locale>
#include <vector>

//#pragma execution_character_set("utf-8")
using namespace std;

string GBKToUTF8(const char* strGBK) {
    int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    string strTemp = str;
    delete[] wstr;
    delete[] str;
    return strTemp;
}

// 注意这个转换函数对头文件有所要求
//string GBKToUTF8(const char* strGBK)
//{
//    int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
//    wchar_t* wstr = new wchar_t[len + 1];
//    memset(wstr, 0, len + 1);
//    MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
//    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
//    char* str = new char[len + 1];
//    memset(str, 0, len + 1);
//    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
//    string strTemp = str;
//    if (wstr) delete[] wstr;
//    if (str) delete[] str;
//    return strTemp;
//}

int teset() {
    setlocale(LC_ALL, "chs");
    // 创建一个Excel文件。
    lxw_workbook* workbook = workbook_new("example2.xlsx");
    lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);

    // 创建一个格式对象
    lxw_format* format_0 = workbook_add_format(workbook);


    // 设置列宽，总和为230mm，这里假设每个列宽单位为1.7mm（Excel中默认的列宽单位）。
    double column_width = 200 / 13;
    for (int col = 0; col < 13; ++col) {
        worksheet_set_column(worksheet, col, col, column_width / 2.54, NULL);
    }


    // 设置字体为微软雅黑，支持中文显示
    format_set_font_name(format_0,"宋体");

    // 设置字体大小
    format_set_font_size(format_0,16);

    // 设置字体颜色
    format_set_font_color(format_0, 0x000000); // 黑色

    // 设置文本为粗体
    //format_set_bold(format);

    // 设置水平和垂直对齐方式为居中
    format_set_align(format_0, LXW_ALIGN_CENTER);
    format_set_align(format_0, LXW_ALIGN_VERTICAL_CENTER);


    // 设置第一行的单元格合并。
    worksheet_merge_range(worksheet, 0, 0, 0, 12, "德州睿阳纱网厂生产单", format_0);

    // 设置第一行表格高度。
    worksheet_set_row(worksheet, 0, 42, NULL);

    lxw_format* format_1 = workbook_add_format(workbook);
    // 设置字体为微软雅黑，支持中文显示
    format_set_font_name(format_1, "宋体");

    // 设置字体大小
    format_set_font_size(format_1, 11);

    // 设置字体颜色
    format_set_font_color(format_1, 0x000000); // 黑色

    // 设置文本为粗体
    //format_set_bold(format);

    // 设置水平和垂直对齐方式为居中
    format_set_align(format_1, LXW_ALIGN_LEFT);
    format_set_align(format_1, LXW_ALIGN_VERTICAL_CENTER);
    // 设置第二行&第三行表格高度。
    worksheet_set_row(worksheet, 1, 22, NULL);
    worksheet_set_row(worksheet, 2, 22, NULL);
    // 合并第二行的单元格，并设置内容。
    //worksheet_write_string(worksheet, 1, 0, "客户:", NULL);
    worksheet_merge_range(worksheet, 1, 0, 1, 3, "客户:", format_1);
    //worksheet_write_string(worksheet, 1, 4, "日期:", NULL);
    worksheet_merge_range(worksheet, 1, 4, 1, 7, "日期:", format_1);
    //worksheet_write_string(worksheet, 1, 7, "备注:", NULL);
    worksheet_merge_range(worksheet, 1, 8, 1, 12, "订单编号:", format_1);
    worksheet_merge_range(worksheet, 2, 4, 2, 7, "颜色:", format_1);
    worksheet_merge_range(worksheet, 2, 8, 2, 12, "备注:", format_1);

    /******************表格内容部分*******************/
    lxw_format* table_format = workbook_add_format(workbook);
    format_set_border(table_format, LXW_BORDER_THIN); // 设置边框
    format_set_font_name(table_format, "宋体"); // 设置字体
    format_set_font_size(table_format, 11); // 设置字体大小
    //format_set_bold(table_format); // 设置粗体
    //format_set_text_wrap(header_format); // 设置文本换行
    format_set_align(table_format, LXW_ALIGN_CENTER); // 设置水平居中
    format_set_align(table_format, LXW_ALIGN_VERTICAL_CENTER); // 设置水平居中

    // 设置第四行表格高度。
    worksheet_set_row(worksheet, 3, 18, NULL);
    std::vector<std::string> headers = {
         "序号", "内径宽", "内径高", "数量", "框宽", "框高", "数量",
        "扇宽", "扇高", "数量", "网宽", "网高", "数量"
    };

    int index = 0;
    for (const auto& header : headers)
    {
        worksheet_write_string(worksheet, 3, index, headers[index].c_str(), table_format);
        index++;
    }
    //worksheet_write_string(worksheet, 2, 0, GBKToUTF8("序号").data(),table_format);

    //for (int col = 0; col < 13; ++col) {
    //    worksheet_write_string(worksheet, 2, col, headers[col], NULL);
    //}

    // 写入数据，这里只是示例，你需要根据实际情况填充数据。
    for (int row = 4; row <= 10; ++row) {
        for (int col = 0; col < 13; ++col) {
            char cell_data[20];
            sprintf_s(cell_data, "%d-%d", row, col);
            worksheet_write_string(worksheet, row, col, cell_data, NULL);
        }
    }

    // 关闭工作簿。
    workbook_close(workbook);

    return 0;
}