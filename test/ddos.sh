#!/bin/bash

url="$1"
port="$2"

if [[ -z $url ]]; then
	echo "Missing url"
	exit 1
fi

get_index() {
    curl -fs $url $port >/dev/null
}

if [[ -n $url ]]; then
	port="-p $port"
fi

while [ true ]; do
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
    get_index &
done
