#!/bin/sh
sort | uniq -c | sort -n | tail -n 1 | awk '{print $2}'

