savedcmd_/home/alw/projects/software/hadlkm/hadmod/hadmod.mod := printf '%s\n'   hadmod.o | awk '!x[$$0]++ { print("/home/alw/projects/software/hadlkm/hadmod/"$$0) }' > /home/alw/projects/software/hadlkm/hadmod/hadmod.mod