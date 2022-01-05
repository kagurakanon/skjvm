#!/usr/bin/env bash

# Font styles
red=$(tput setaf 1)
green=$(tput setaf 2)
yellow=$(tput setaf 3)
blue=$(tput setaf 4)
bold=$(tput bold)
reset=$(tput sgr0)

# Badges
info="${bold}${blue}[$0 info]${reset}"
success="${bold}${green}[$0 success]${reset}"
warning="${bold}${yellow}[$0 warning]${reset}"
error="${bold}${red}[$0 error]${reset}"

function help {
  echo -e "usage: ${bold}$0 <command>${reset}"
  echo -e "  where command include:"
  echo -e "    build       build the project with CMake and GNU Make"
  echo -e "    test        run tests (unimplemented)"
  echo -e "    clean       clean the project"
  echo -e "    help        show this help"
}

if [[ $# != 1 ]]; then
  echo -e "${error} Expected 1 argument, got $#."
  help
  exit 1
fi

case $1 in
  build)
    echo -e "${info} Create build directory and run CMake."
    cmake -S . -B build -G "Unix Makefiles"

    echo -e "${info} Run GNU Make (Unix Makefiles), build project"
    cmake --build build
    
    echo -e "${success} Build success."
    ;;
  test)
    echo -e "${error} Test not implemented."
    ;;
  clean)
    if [[ -d "./build" ]]; then
      echo -e "${info} Remove build directory."
      rm -rf build
      echo -e "${success} Clearance complete."
    else
      echo -e "${warning} Nothing to clean."
    fi
    ;;
  help)
    help
    ;;
  *)
    echo -e "${error} Unknown command: ${bold}$1${reset}, see usage below."
    help
    exit 1
    ;;
esac
