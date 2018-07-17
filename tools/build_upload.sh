#!/bin/bash
make -C ../../ software PROGRAM=motor_movement BOARD=freedom-e300-hifive1
make -C ../../ upload PROGRAM=motor_movement BOARD=freedom-e300-hifive1
