#!/bin/sh

killall -9 test_prg
rm /dev/shm/sem*
rm /dev/shm/mytesting*
rm /dev/mqueue/*
tput init
stty sane
make clean

