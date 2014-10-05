#!/bin/bash

set -e

rm cachegrind.out.* || true

valgrind --tool=cachegrind ../tests/bstree_tests
cg_annotate --show=Dr,Dw `ls -1 cachegrind.out.*` | grep -v "???:"
