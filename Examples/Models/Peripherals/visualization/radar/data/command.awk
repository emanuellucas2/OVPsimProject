BEGIN {
    TIMESTAMP = 0;
}

/\$GPGGA/ {
#    printf("<TRAFFIC>\n");
}

#
# Ownship Record
#
/\$GPRMC/ {
    KNS=$8;
    TRACK=$9;
    TIMESTAMP++;

    printf("OWNSHIP TIMESTAMP=%d TRACK=%d KNS=%d\n", TIMESTAMP, TRACK, KNS);

#    printf("  <INFO>\n");
#    printf("    <TIMESTAMP>%d</TIMESTAMP>\n", TIMESTAMP);
#    printf("    <TRACK>%d</TRACK>\n", TRACK);
#    printf("    <KNS>%d</KNS>\n", KNS);
#    printf("  </INFO>\n");
}

#
# Traffic Record
#
/\$PFLAA/ {
    Y=$3;
    X=$4;
    Z=$5;
    ICAO=$7;
    TRACK=$8;
    KNS=$10;
    CLIMB=$11;

    printf("AIRCRAFT ICAO=%s X=%d Y=%d Z=%d KNS=%d TRACK=%d CLIMB=%d\n", ICAO, X, Y, Z, KNS, TRACK, CLIMB);

    #printf("  <AC>\n");
    #printf("    <ICAO>%d</ICAO>\n", ICAO);
    #printf("    <XY>1</XY>\n");
    #printf("    <X>%d</X>\n", X);
    #printf("    <Y>%d</Y>\n", Y);
    #printf("    <Z>%d</Z>\n", Z);
    #printf("    <KNS>%d</KNS>\n", KNS);
    #printf("    <TRACK>%d</TRACK>\n", TRACK);
    #printf("    <CLIMB>%d</CLIMB>\n", CLIMB);
    #printf("  </AC>\n");
}

/\$PFLAU/ {
#    printf("</TRAFFIC>\n");
}

 
