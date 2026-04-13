void PlayWarppadSound(u_int distance)
{
    CalculateVolumeFromDistance(&sdata->soundFadeInput[0].soundID_soundCount, 152, distance);
}