/* 2023-02-01 */
#include <iostream>
#include <string>
#include <regex>

const char * HEAD="\
<!DOCTYPE html>\
<html>\
<head>\
<meta charset=\"utf-8\">\
<meta http-equiv=\"Content-Security-Policy\" content=\"upgrade-insecure-requests\">\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
<link type=\"text/css\" rel=\"stylesheet\" href=\"/style.css\">\
<link type=\"text/css\" rel=\"stylesheet\" href=\"style.css\">\
<title>Mirrored Gemini content.</title>\
</head>\
<body>\
";

const char * FEET="\
</body>\
</html>\
";

const char * HELP="Gemini to HTML converter, 2022 Marius Alpmann\n\n\
Usage: Give gemini text to stdin. You will receive a corresponding HTML\n\
       file on stdout\n\
Example: cat index.gmi | ./gmi2html.sh > index.html\
";

int main(int argc, char * argv[]) {
	bool inCodeblock = false;

	if(argc == 2) {
		if(std::string(argv[1]) == "-h") {
			std::cout << HELP << std::endl;
			return 0;
		}
	}

	std::cout << HEAD;
	std::cin.sync();
	for(std::string line; std::getline(std::cin, line);) {
		if(line.substr(0, 3) == "```") {
			if(!inCodeblock)
				std::cout << "<pre>";
			else
				std::cout << "</pre>";

			inCodeblock = !inCodeblock;
		}
		
		else if(inCodeblock) {
			// Remove <'s and >'s to allow for HTML code display
			line = std::regex_replace(line, std::regex("<"), "&lt;");
			line = std::regex_replace(line, std::regex(">"), "&gt;");

			std::cout << line << std::endl;
		}

		else if(line == "")
			continue;
		
		else if(line.substr(0, 3) == "###")
			std::cout << "<h3>" << line.substr(3) << "</h3>";
		else if(line.substr(0, 2) == "##")
			std::cout << "<h2>" << line.substr(2) << "</h2>";
		else if(line.substr(0, 1) == "#")
			std::cout << "<h1>" << line.substr(1) << "</h1>";
		
		else if(line.substr(0, 2) == "* ")
			std::cout << "<ul><li>" << line.substr(2) << "</li></ul>";

		else if(line.substr(0, 1) == ">")
			std::cout << "<blockquote>" << line.substr(1) << "</blockquote>";

		else if(line.substr(0, 3) == "=> ") {
			line = std::regex_replace(line, std::regex("\\.gmi"), ".html");

			auto spacepos = line.find(' ', 3);
			std::string linkdesc;
			std::string linkloc;
			std::string ext;

			// no space found (= no link description)
			if(spacepos == std::string::npos) {
				linkloc = line.substr(3);
				linkdesc = linkloc;
			} else {
				linkloc = line.substr(3, spacepos-3);
				linkdesc = line.substr(spacepos);
			}

			auto pointpos = linkloc.rfind('.');
			// no point found (= no filename extension)
			if(pointpos == std::string::npos) {
				std::cout << "<a href=\"" << linkloc << "\">" << linkdesc << "</a><br>";
				continue;
			} else {
				// Filename extension without the full stop (+1)
				if(spacepos == std::string::npos)
					ext = linkloc.substr(pointpos+1);
				else
					ext = linkloc.substr(0, spacepos).substr(pointpos+1);
			}

			if(ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "avif" || ext == "jxl" || ext == "webp") {
				std::cout << "<figure><img src=\"" << linkloc << "\"><figcaption>" << linkdesc << "</figcaption></figure>";
			}
			else if(ext == "mp4" || ext == "mkv" || ext == "webm") {
				std::cout << "<figure><video controls><source src=\"" << linkloc << "\">It seems your browser cannot display this video. <a href=\"" << linkloc << "\"Click here to download it instead.</a></video><figcaption>" << linkdesc << "</figcaption></figure>";
			}
			else if(ext == "mp3" || ext == "opus" || ext == "ogg" || ext == "wav" || ext == "flac") {
				std::cout << "<figure><audio controls src=\"" << linkloc << "\">It seems your browser cannot play back this audio. <a href=\"" << linkloc << "\">Click here to download it instead.</a></audio><figcaption>" << linkdesc << "</figcaption></figure>";
			} else
				std::cout << "<a href=\"" << linkloc << "\">" << linkdesc << "</a><br>";
		}

		else
			std::cout << "<p>" << line << "</p>";

	}

	std::cout << FEET << std::endl;

	return 0;
}
