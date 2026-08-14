#ifndef BUNDLES_H
#define BUNDLES_H

int bundle_builtins(struct command cmd, char* tempPath);
int bundle_executables(struct command cmd, char* tempPath,char* execPath);
#endif