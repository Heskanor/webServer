#include "Response.hpp"

int main()
{
	Request req;
	req.setmethod("GET");
	req.setrequest("/Desktop/test.php");
	req.sethttpversion("HTTP/1.1");
	std::string file = "/Users/ashite/Desktop/test.php";
	int haha = get_file_size(file);
	req.setcontent_length(better_to_string(haha));
	req.setcontent_type("text/x-php");
	req.set_pathbody("/Users/ashite/Downloads/cry.jpeg");

	Server serv;
	Location loc1;
	Location loc2;
	Location loc3;
	Location loc4;

	std::map<std::string, std::string> err_map;
	serv.add_error_map("400", "/Desktop/webserver/ErrorPages/400.html");
	serv.add_error_map("403", "/Desktop/webserver/ErrorPages/403.html");
	serv.add_error_map("404", "/Desktop/webserver/ErrorPages/404.html");


	loc1.set_root("/Users/ashite");
	loc1.set_path("/Desktop");
	std::vector<std::string> indexes;
	indexes.push_back("ngin.txt");
	loc1.set_index(indexes);
	loc1.set_auto_index(true);
	// loc1.set_upload_directory("/Desktop/CPP_pool/");
	std::vector<std::string> allowed_methods;
	allowed_methods.push_back("GET");
	allowed_methods.push_back("POST");
	loc1.set_allowed_methods(allowed_methods);
	// loc1.set_redirection("301", "http://www.codeforces.com/");
	loc1.set_cgi_path("/usr/bin/php");
	std::vector<std::string> v_ext;
	v_ext.push_back(".php");
	loc1.set_cgi_ext(v_ext);



	loc2.set_root("/Users/ashite/Desktop");
	loc2.set_path("/CPP_pool");
	std::vector<std::string> indexes2;
	indexes2.push_back("comp.html");
	indexes2.push_back("pool.txt");
	loc2.set_index(indexes2);
	loc2.set_auto_index(false);
	loc2.set_upload_directory("");
	std::vector<std::string> allowed_methods2;
	allowed_methods2.push_back("GET");
	allowed_methods2.push_back("DELETE");
	loc2.set_allowed_methods(allowed_methods2);

	loc3.set_root("/Users/ashite");
	loc3.set_path("/Downloads");
	std::vector<std::string> indexes3;
	indexes3.push_back("ngin.txt");
	indexes3.push_back("pool.html");
	loc3.set_index(indexes3);
	loc3.set_auto_index(true);
	loc3.set_upload_directory("");
	std::vector<std::string> allowed_methods3;
	allowed_methods3.push_back("GET");
	allowed_methods3.push_back("POST");
	loc3.set_allowed_methods(allowed_methods3);


	loc4.set_root("/Users/ashite/Desktop");
	loc4.set_path("/Tobedeleted");
	std::vector<std::string> indexes4;
	indexes4.push_back("index.txt");
	indexes4.push_back("file.html");
	loc4.set_index(indexes4);
	loc4.set_auto_index(true);
	loc4.set_upload_directory("");
	std::vector<std::string> allowed_methods4;
	allowed_methods4.push_back("GET");
	allowed_methods4.push_back("DELETE");
	loc4.set_allowed_methods(allowed_methods4);

	serv.add_location(loc1);
	serv.add_location(loc2);
	serv.add_location(loc3);
	serv.add_location(loc4);

	Response res = server_response(req, serv);
	std::cout << "------------------------------------" << std::endl;
	std::cout << res._status_code << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << res._headers << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << res._body_path << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << res._tmp_file_path << std::endl;
	std::cout << "------------------------------------" << std::endl;
}