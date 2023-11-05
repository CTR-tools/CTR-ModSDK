// Get Level ID from String
int MainInit_StringToLevID(char *levString)
{
    for (char i = 0; i < 0x41; i++)
    {
        if (strcmp(data.metaDataLEV[i].name_Debug, levString) == 0)
        {
            return i; // Return the Level ID when a match is found
        }
    }
    return 0;
}