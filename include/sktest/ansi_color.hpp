#ifndef sktest_ansi_color_hpp
#define sktest_ansi_color_hpp

#define BOLD_RED "\033[31;1m"
#define RED "\033[31m"

#define BOLD_GREEN "\033[32;1m"
#define GREEN "\033[32m"

#define BLUE "\033[34m"

#define BOLD "\033[1m"
#define RESET "\033[0m"

#define bold_red(string) BOLD_RED string RESET
#define red(string) RED string RESET

#define bold_green(string) BOLD_GREEN string RESET
#define green(string) GREEN string RESET

#define blue(string) BLUE string RESET

#define bold(string) BOLD string RESET

#endif /* sktest_ansi_color_hpp */