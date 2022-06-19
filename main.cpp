#include "Response.cpp"

int main()
{
	Request req;
	req.setmethod("GET");
	req.setrequest("/Desktop");
	req.sethttpversion("HTTP/1.1");
	req.setcontent_length("0");
	req.setcontent_type("text/html");

	Server serv;
	Location loc1;
	Location loc2;
	loc1.set_root("/home/sigma");
	loc1.set_path("/Desktop");
	std::vector<std::string> indexes = {"ngin.txt", "pool.html"};
	loc1.set_index(indexes);
	loc1.set_auto_index(true);
	loc1.set_upload_directory("");
	std::vector<std::string> allowed_methods = {"GET", "POST"};
	loc1.set_allowed_methods(allowed_methods);

	loc2.set_root("/home/sigma/Desktop");
	loc2.set_path("/ACPC");
	std::vector<std::string> indexes2 = {"chill.txt", "comp.html"};
	loc2.set_index(indexes2);
	loc2.set_auto_index(false);
	loc2.set_upload_directory("");
	std::vector<std::string> allowed_methods2 = {"GET", "DELETE"};
	loc2.set_allowed_methods(allowed_methods2);

	serv.add_location(loc1);
	serv.add_location(loc2);

	Response res = server_response(req, serv);
	std::cout << res._status_code << std::endl;
	std::cout << res._body_path << std::endl;
	std::cout << res._headers << std::endl;
}