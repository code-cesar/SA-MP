
#pragma once

#include <stdio.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include <stdint.h>
#include <assert.h>
#include <Windows.h>
#include <process.h>
#include <vector>
#include "detours.h"
#pragma comment(lib, "detours.lib")

#include "BitStream.h"
#include "RakClient.h"
#include "HookedRakClient.h"
#include "samp.h"

extern SAMPFramework *pSAMP;
