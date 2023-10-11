// param_1 either cutscene obj or ModelHeader
char DECOMP_CS_Instance_BoolPlaySound(struct CutsceneObj *cs, struct Instance *desiredInst)
{
    struct Instance *inst;
    struct Instance **visInst;

    if ((desiredInst == NULL) || ((cs->flags & 0x1000) == 0))
        return 1;
    
    // pointer to array of visible instances
    visInst = sdata->gGT->cameraDC[0].visInstSrc;

    // first instance
    for (inst = visInst[0];
         // if instance is valid
         inst != NULL;
         // next instance
         inst = *(++visInst))
    {
        // if instance is found, quit
        if (inst == desiredInst)
        {
            return (desiredInst->idpp[0].unkb8[0] & 0x40) != 0;
        }
    }
    return 0;
}