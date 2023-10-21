#include <common.h>

void COLL_ResetScratchpadCache(struct ScratchpadStruct* sps)
{
  u_int *in_t8; // t8 is address of first LevVertex in level

  // for (char i = 0; i < 9; i++) ?

  // [0]
  *(u_int*)&sps->bspSearchVert[0].pos[0] = in_t8[0];
  *(u_int*)&sps->bspSearchVert[0].pos[2] = in_t8[1];
  *(u_int**)&sps->bspSearchVert[0].normalVec[0] = in_t8;
  
  // [1]
  *(u_int*)&sps->bspSearchVert[1].pos[0] = in_t8[0x23ca0];
  *(u_int*)&sps->bspSearchVert[1].pos[2] = in_t8[0x23ca1];
  *(u_int**)&sps->bspSearchVert[1].normalVec[0] = in_t8 + 0x23ca0;
  *(u_int**)&sps->bspSearchVert[1].normalVec[2] = 0x8f290004;
  
  // [2]
  *(u_int*)&sps->bspSearchVert[2].pos[0] = in_t8[0x10];
  *(u_int*)&sps->bspSearchVert[2].pos[2] = in_t8[0x11];
  *(u_int**)&sps->bspSearchVert[2].normalVec[0] = in_t8 + 0x10;
  
  // [3]
  *(u_int*)&sps->bspSearchVert[3].pos[0] = in_t8[0x23ca4];
  *(u_int*)&sps->bspSearchVert[3].pos[2] = in_t8[0x23ca5];
  *(u_int**)&sps->bspSearchVert[3].normalVec[0] = in_t8 + 0x23ca4;
  
  // [4]
  *(u_int*)&sps->bspSearchVert[4].pos[0] = in_t8[0x3fffc];
  *(u_int*)&sps->bspSearchVert[4].pos[2] = in_t8[0x3fffd];
  *(u_int**)&sps->bspSearchVert[4].normalVec[0] = in_t8 + 0x3fffc;
  
  // [5]
  *(u_int *)&sps->bspSearchVert[5].pos[0] = in_t8[0xc40c];
  *(u_int *)&sps->bspSearchVert[5].pos[2] = in_t8[0xc40d];
  *(u_int **)&sps->bspSearchVert[5].normalVec[0] = in_t8 + 0xc40c;
  
  // [6]
  *(u_int *)&sps->bspSearchVert[6].pos[0] = in_t8[0x6400];
  *(u_int *)&sps->bspSearchVert[6].pos[2] = in_t8[0x6401];
  *(u_int **)&sps->bspSearchVert[6].normalVec[0] = in_t8 + 0x6400;
  
  // [7]
  *(u_int *)sps->bspSearchVert[7].pos[0] = in_t8[0xc];
  *(u_int *)sps->bspSearchVert[7].pos[2] = in_t8[0xd];
  *(u_int **)sps->bspSearchVert[7].normalVec[0] = in_t8 + 0xc;
  
  // [8]
  *(u_int *)sps->bspSearchVert[8].pos[0] = in_t8[0x6084];
  *(u_int *)sps->bspSearchVert[8].pos[2] = in_t8[0x6085];
  *(u_int **)sps->bspSearchVert[8].normalVec[0]= in_t8 + 0x6084;
}
