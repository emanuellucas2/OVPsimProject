#!/bin/bash

awk -f command.awk -F ',' $1 > $2
