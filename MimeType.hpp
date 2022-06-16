class MimeType
{
	public:
		std::map<std::string, std::string> mimeTypes;

	public:
		MimeType() {
			mimeTypes[".html"] = "text/html";
			mimeTypes[".htm"] = "text/html";
			mimeTypes[".css"] = "text/css";
			mimeTypes[".js"] = "application/javascript";
			mimeTypes[".jpg"] = "image/jpeg";
			mimeTypes[".jpeg"] = "image/jpeg";
			mimeTypes[".png"] = "image/png";
			mimeTypes[".gif"] = "image/gif";
			mimeTypes[".ico"] = "image/x-icon";
			mimeTypes[".svg"] = "image/svg+xml";
			mimeTypes[".json"] = "application/json";
			mimeTypes[".pdf"] = "application/pdf";
			mimeTypes[".zip"] = "application/zip";
			mimeTypes[".rar"] = "application/x-rar-compressed";
			mimeTypes[".7z"] = "application/x-7z-compressed";
			mimeTypes[".gz"] = "application/gzip";
			mimeTypes[".bz2"] = "application/bzip2";
			mimeTypes[".doc"] = "application/msword";
			mimeTypes[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
			mimeTypes[".xls"] = "application/vnd.ms-excel";
			mimeTypes[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
			mimeTypes[".ppt"] = "application/vnd.ms-powerpoint";
			mimeTypes[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
			mimeTypes[".odt"] = "application/vnd.oasis.opendocument.text";
			mimeTypes[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
			mimeTypes[".odp"] = "application/vnd.oasis.opendocument.presentation";
			mimeTypes[".xml"] = "text/xml";
			mimeTypes[".mp3"] = "audio/mpeg";
			mimeTypes[".wav"] = "audio/x-wav";
			mimeTypes[".wma"] = "audio/x-ms-wma";
			mimeTypes[".ogg"] = "audio/ogg";
			mimeTypes[".mp4"] = "video/mp4";
			mimeTypes[".webm"] = "video/webm";
			mimeTypes[".mkv"] = "video/x-matroska";
			mimeTypes[".avi"] = "video/x-msvideo";
			mimeTypes[".wmv"] = "video/x-ms-wmv";
			mimeTypes[".mov"] = "video/quicktime";
			mimeTypes[".c"] = "text/x-csrc";
			mimeTypes[".cpp"] = "text/x-c++src";
			mimeTypes[".h"] = "text/x-chdr";
			mimeTypes[".hh"] = "text/x-c++hdr";
			mimeTypes[".hpp"] = "text/x-c++hdr";
			mimeTypes[".cxx"] = "text/x-c++src";
			mimeTypes[".cc"] = "text/x-c++src";
			mimeTypes[".java"] = "text/x-java";
			mimeTypes[".cs"] = "text/x-csharp";
			mimeTypes[".pl"] = "text/x-perl";
			mimeTypes[".rb"] = "text/x-ruby";
			mimeTypes[".py"] = "text/x-python";
			mimeTypes[".php"] = "text/x-php";
			mimeTypes[".sh"] = "text/x-shellscript";
			mimeTypes[".txt"] = "text/plain";
			mimeTypes[""] = "";
		}
		~MimeType() {
			mimeTypes.clear();
		}
		std::string const &get_mime_type(std::string const &ext) {
			return mimeTypes[ext];
		}
		std::string const &get_extension(std::string const &mime) {
			for (std::map<std::string, std::string>::iterator it = mimeTypes.begin(); it != mimeTypes.end(); ++it) {
				if (it->second == mime)
					return it->first;
			}
			return mimeTypes[""];
		}
};