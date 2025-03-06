#!/bin/bash

url="10.19.230.85:8080"

get_index() {
    curl -fs $1 >/dev/null
}

while [ true ]; do
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
    get_index $url &
done