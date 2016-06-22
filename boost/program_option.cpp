/*
 *
 * Date: 2016/5/19
 * Target: How to grab options which are parameters as input data when starting program.
 * Compile: g++ -std=c++0x -o opt program_options.cpp -lboost_program_options -lboost_system
 *
 */
// Standard Libraries
#include <iostream>

// Boost Libraries
#include <boost/program_options.hpp> // for boost::program_options
#include <boost/filesystem.hpp> // for boost::filesystem

// make your options.
struct Options {
	bool isMale;
	std::string Name;
	int age;
	std::string profile_path;
};

int main(int argc, char **argv) {
	Options opts;

	// creating the instance of option class. Which of name is 'Options'.
	boost::program_options::options_description desc("Options");

	// make our options, default values, and descriptors ...
	desc.add_options()
		("help,h", "produce help message")
		("ismale,m", boost::program_options::value<bool>(&opts.isMale)->default_value(true), "Is this a male?")
		("name,n", boost::program_options::value<std::string>(&opts.Name)->default_value("Jack"), "What's your name?")
		("age,a", boost::program_options::value<int>(&opts.age)->default_value(10), "How old are you?")
		("profile-path,p", boost::program_options::value<std::string>(&opts.profile_path)->default_value("/opt"), "Where is the profile?")
		;

	boost::program_options::variables_map vm;

	try {
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv)
									.options(desc)
									.run()
									,vm);
	} catch(std::exception &err) {
		std::cerr << "\nError parsing command line: " << err.what() << std::endl;
		return 1;
	}

	boost::program_options::notify(vm);

	// once program gets the "help", print out all of descriptors and then exit.
	if(vm.count("help")) {
		std::cout << "Usage: options_description [options]\n";
		std::cout << desc;
		return 1;
	}

	std::cout << "Sex: " << ((opts.isMale) ? "Male" : "Female") << std::endl;

	return 0;
}