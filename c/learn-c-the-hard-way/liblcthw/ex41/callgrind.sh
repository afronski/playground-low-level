#!/bin/bash

set -e

rm callgrind.out.* || true

valgrind --dsymutil=yes --tool=callgrind ../tests/bstree_tests
callgrind_annotate `ls -1 callgrind.out.*` | grep -v "???:"

pushd ../

  callgrind_annotate `ls -1 ex41/callgrind.out.*` src/lcthw/bstree.c | grep -v "???:" 

popd
