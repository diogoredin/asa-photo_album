#!/bin/bash

# =========== CONSTANTS ===========
# Return values
readonly RET_success=0
readonly RET_error=1
readonly RET_usage=2
readonly RET_help=2

# Colors
readonly RCol='\033[0m'                 # Text Reset
readonly Whi='\033[0;37m'               # White, for small details
readonly Red='\033[0;31m'               # Red, for small details
readonly Gre='\033[0;32m'               # Green, for small details
readonly Yel='\033[0;33m'               # Yellow, for mid-building
readonly BRed='\033[1;31m'              # Bold Red, when an error occurred
readonly BGre='\033[1;32m'              # Bold Green, for successes
readonly BYel='\033[1;33m'              # Bold Yellow, when building stuff
readonly BWhi='\033[1;37m'              # Bold White, when beginning something
readonly URed='\033[4;31m'              # Underline Red, for warnings
readonly UGre='\033[4;32m'              # Underline Green, for smaller successes
readonly UBlu='\033[4;34m'              # Underline Blue, for links
readonly UWhi='\033[4;37m'              # Underline White, for commands

# Strings
readonly Note="${UWhi}Notice${Whi}:${RCol}"
readonly Warn="${BYel}Warning${Yel}:${RCol}"
readonly Err="${BRed}Error${Red}:${RCol}"

readonly ScriptName="$0"

# String Arrays
readonly usage_content=( "Usage: $(basename $ScriptName)"
"HELP:
	-h | --help : Shows this message"
"FILES & DIRECTORIES:
	-e : Specify executable
	-t : Specify tests directory"
"OPTIONS:
	-m | --use-valgrind : Enables testing with valgrind (good for memory tracking)
	--show-all : Prints successes as well"
)

# Files & Directories
readonly DIR_current="$(pwd)"

# Options
BOOL_recursive=true
BOOL_showAll=false

# =========== FUNCTIONS ===========
function usage {
	for i in `seq 0 ${#usage_content[@]}`; do
		echo -e "${usage_content[i]}"
	done
    exit $RET_usage
}

function get_absolute_dir {
	# $1 : directory to parse
	cd "$1" > /dev/null
	temp_dir="$(pwd)"
	cd - > /dev/null
	echo "$temp_dir"
}

function parse_args {
	if [ $# -eq 0 ]; then return 0; fi

	while [ $# -gt 0 ]; do
		case $1 in
			# DIRECTORIES
			-t )
				shift
				DIR_tests="$(get_absolute_dir "$1")"
				BOOL_recursive=false
				;;
			# OPTIONS
			-m | --use-valgrind )
				useValgrind="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --db-attach=yes"
				;;
			--show-all )
				BOOL_showAll=true
				;;
			# HELP
			-h|--help )
				usage
				exit $RET_usage
				;;
			* ) printf "Unknown argument. \"$1\"\n"
				;;
		esac
		shift
	done

	return $RET_success
}

function print_progress {
	# $1 : text to print
	# $2+: formatting args
	printf "\n${BYel}$1\n${RCol}" ${@:2}
}
function print_success {
	# $1 : text to print
	# $2+: formatting args
	printf "\n${UGre}SUCCESS${Gre}:${RCol} $1\n${RCol}" ${@:2}
}
function print_failure {
	# $1 : text to print
	# $2+: formatting args
	printf "\n${URed}FAILURE${Red}:${RCol} $1\n" ${@:2}
}
function print_error {
	# $1 : text to print
	# $2+: formatting args
	printf "\n${BRed}ERROR${Red}:${RCol} $1\n" ${@:2}
}

function set_env {
	# Defining script directories
	cd "$(dirname "$0")"
	DIR_script="$(pwd)"
	DIR_project="$(cd $DIR_script/..; pwd)"

	if [ -z "$EXEC_prog" ]; then
		EXEC_prog="$DIR_project/bld/proj"
	fi
}
function check_env {
	# Checking executable
	if [ ! -e $EXEC_prog ]; then
		print_error "\"$EXEC_prog\" does not exist."
		return $RET_error
	elif [ ! -x $EXEC_prog ]; then
		print_error "\"$EXEC_prog\" is not an executable."
		return $RET_error
	fi

	# Checking valgrind
	if [ "$useValgrind" -a -z "$(which valgrind)" ]; then
		print_error "valgrind is not installed."
		return $RET_error
	fi
}

# Target functionality
function test_dir {
	# $1 : test directory
	if [ $# -lt 1 ]; then
		print_error "test_dir: No arguments given."
		return $RET_error
	elif [ ! -d "$1" ]; then
		print_error "Given argument is not a directory."
		return $RET_error
	elif [ -z "$(ls $1/*.in 2> /dev/null)" -o -z "$(ls $1/*.out 2> /dev/null)" ]; then
		print_error "Given directory does not contain any test files."
		return $RET_error
	fi

	# Run tests
	local fail_count=0
	for test_input in $1/*.in; do
		local test_output = "${test_input%.in}.out"
		local test_outhyp = "${test_input%.in}.outhyp"
		local test_result = "${test_input%.in}.diff"

		# Running program
		if [ "$useValgrind" ]; then
			$useValgrind $EXEC_prog < $test_input
		else
			$EXEC_prog < $test_input > $test_outhyp
		fi

		if [ $? -ne 0 ]; then
			return $RET_error
		fi

		# Comparing results
	    diff $test_output $test_outhyp > $test_result

		# Act accordingly
		local test_name="$(basename $1)/$(basename $test_input)"
		if [ -s $test_result ]; then
	        print_failure "$test_name. See file $test_result"
			fail_count=$(($fail_count + 1))
	    else
			if [ $BOOL_showAll == true ]; then
				print_success "$test_name"
			fi
	        rm -f $test_result $test_outhyp
	    fi
	done

	local total_count=$((ls -f "*.in" | wc -l))
	if [ $fail_count -gt 0 ]; then
		print_failure "Failed $fail_count / $total_count tests."
	fi

	return $fail_count
}

function cleanup {
	: # Nothing to clean
}

function main {
	parse_args "$@"
	set_env
	check_env
	if [ $? -eq $RET_error ]; then
		usage
		exit $RET_error
	fi

	local retval=$RET_success
	local fail_count=0
	if [ $BOOL_recursive == true ]; then
		for x in $DIR_script/*/; do
			print_progress "Running through \"$x\""
			test_dir "$x"
			fail_count=$(($fail_count + $?))
		done
	else
		test_dir "$DIR_tests"
		fail_count=$?
	fi
	cleanup

	exit $fail_count
}

# Script starts HERE
main "$@"
