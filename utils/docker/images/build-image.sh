#!/usr/bin/env bash
# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2016-2021, Intel Corporation

#
# build-image.sh - prepares a Docker image with <OS>-based
#                           environment for testing pmemkv, according
#                           to the Dockerfile.<OS-VER> file located
#                           in the same directory.
#
# The script can be run locally.
#

set -e

if [[ -z "${OS}" || -z "${OS_VER}" ]]; then
	echo "ERROR: The variables OS and OS_VER have to be set " \
		"(e.g. OS=fedora, OS_VER=32)."
	exit 1
fi

if [[ -z "${CONTAINER_REG}" ]]; then
	echo "ERROR: CONTAINER_REG environment variable is not set " \
		"(e.g. \"<registry_addr>/<org_name>/<package_name>\")."
	exit 1
fi

echo "Check if the file Dockerfile.${OS}-${OS_VER} exists"
if [[ ! -f "Dockerfile.${OS}-${OS_VER}" ]]; then
	echo "Error: Dockerfile.${OS}-${OS_VER} does not exist."
	exit 1
fi

TAG="1.4-${OS}-${OS_VER}"

echo "Build a Docker image tagged with: ${CONTAINER_REG}:${TAG}"
docker build -t ${CONTAINER_REG}:${TAG} \
	--build-arg http_proxy=$http_proxy \
	--build-arg https_proxy=$https_proxy \
	-f Dockerfile.${OS}-${OS_VER} .
