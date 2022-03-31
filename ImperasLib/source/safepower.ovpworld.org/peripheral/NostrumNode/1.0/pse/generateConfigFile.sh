#!/bin/bash

# name of config file to generate
CFGFILE=channel_config.inf

echo "Started ..."
find . -type f -name "software_configuration.h | \
     xargs grep "#define .*channel_" | \
     sed -e "s|\./||" \
         -e "s|_app.*:#define | |" \
  > $CFGFILE
dos2unix $CFGFILE

sed -i -e "s|send_channel_|send |" \
       -e "s|recv_channel_|recv |" \
    $CFGFILE

sed -i -e "s|_to_| to |" \
       -e "s|_from_| from |" \
    $CFGFILE

sed -i -e "s|cpu_0_0|0|" \
       -e "s|cpu_0_1|1|" \
       -e "s|cpu_1_0|2|" \
       -e "s|cpu_1_1|3|" \
       -e "s|A9_0|0|" \
    $CFGFILE

getProcessList () {
  node=$1
  grep "^${node} " $CFGFILE | sed -e "s|.* \(p.*\) [tf].*| \1|" | sort -u | tr -d '\n'
}

echo "Update process with node number"
for n in 0 1 2 3; do
  for p in  $(getProcessList ${n}); do
    sed -i -e "s| ${p} | ${p} ${n} |" $CFGFILE
  done
done

echo "Complete ..."
