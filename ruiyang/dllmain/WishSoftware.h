#pragma once
#include "xlsxwriter.h"
#include <iostream>
#include <vector>

// 表格行数据结构
struct TableRow {
	int serial_number;
	int inner_width;
	int inner_height;
	int quantity;
	int frame_width;
	int frame_height;
	//int quantity_frame;
	int fan_width;
	int fan_height;
	//int quantity_fan;
	int net_width;
	int net_height;
	//int quantity_net;
	int price;
};
struct DoorWindow
{
	int frame_width_vary;
	int frame_height_vary;
	int fan_width_vary;
	int fan_height_vary;
	int net_width_vary;
	int net_height_vary;

};

struct ProductTable
{
	int row1;
	int row2;
	int row3;
	int row4;
	int data_row;
};
struct SaleTable
{
	int length;
	int row1;
	int row2;
	int row3;
	int row4;
	int data_row;
	int row5_6;
	int row7;
	int row8;
};



struct ProductRow
{
	bool checked;
	int  p_id;
	std::vector<int> data;
};

class WishSoftware
{
public:
	WishSoftware();
	~WishSoftware();

	
	void draw_table();

	void draw_menu();

	//隐藏窗口的TabBar
	void hideTabBar();

	void draw_product_style_window();
	void draw_product_style_table();
	void draw_price_style_table();

	void draw_product_xlxs_window();
	void draw_sale_xlxs_window();

	void draw_param_setting_window();

	int show_window();

	std::vector<std::vector<int>> read_priceCSV(const std::string& filename);

	void write_priceCSV(const std::string& filename, const std::vector<std::vector<int>>& data);

	void init_priceData();

	void write_productXML();
	void read_productXML();

	void update_door_window_vary();

	void update_price();
	void update_price_new();

	void get_current_time();

	void create_xlsx();

	void create_product_xlsx();
	void create_sale_xlsx();

	void init_format_xlsx();

	void read_paramSetting();
	void write_paramSetting();
	
private:

	static void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	std::vector<TableRow> tableData;

	int currentRowCount;
	bool show_main_window;
	bool show_product_setting_window;
	bool show_price_setting_window;
	bool show_param_setting_window;
	bool opt_fullscreen;

	bool button_priceSave_clicked;

	bool show_product_xlsx;
	bool show_sale_xlsx;

	//product type
	std::vector<ProductRow> product_rows;


	int price_whole;
	int price_whole_;
	int num_whole;
	int price_mask;
	int frame_width_threshold;
	int frame_height_thmin;
	int frame_height_thmax;
	//
	char textBuffer_name[256];
	char textBuffer_name2[256];
	char textBuffer_custmor[256];
	char textBuffer_custmor_phone[256];
	char textBuffer_custmor_address[256];
	char textBuffer_color[256];
	char textBuffer_backup[256];
	char textBuffer_address[256];
	char textBuffer_phone[256];


	//std::string textBuffer_str_name;
	//std::string textBuffer_str_name2;
	//std::string textBuffer_str_custmor;
	//std::string textBuffer_str_custmor_address;
	//std::string textBuffer_str_color;
	//std::string textBuffer_str_backup;
	//std::string textBuffer_str_address;
	//std::string textBuffer_str_phone;

private:

	//price data 
	std::vector<std::vector<int>>  price_data;
	std::string m_priceData_fileName;
	std::string m_productData_fileName;
	//product data
	int selection ;

	DoorWindow door_window;

	std::string current_date;
	std::string order_numer;

private:  //xlsxwriter
	std::string xlsx_file_name;

	lxw_workbook* workbook;
	lxw_worksheet* worksheet1;
	lxw_worksheet* worksheet2;
	lxw_format* format_topic;
	lxw_format* format_info;
	lxw_format* format_table;

	ProductTable product_table;
	SaleTable sale_table;

	std::string numberToChinese(int number);
	std::string formatCurrency(double amount);
};

