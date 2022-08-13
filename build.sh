for dotc_file in ./src/*.c; do
  clang -g -fPIC -c "$dotc_file" -I./include/ -I./src/ -o "$dotc_file.o"
done

doto_files=""

for doto_file in ./src/*.c.o; do
  doto_files="${doto_files} ${doto_file}"
done

ar rcs bin/librefqueue.a $doto_files
clang -g -shared -o bin/librefqueue.so $doto_files
 
clang -g -o bin/program program/program.c -I./include -L./bin -l:librefqueue.a

rm ./src/*.c.o


install='install'
uninstall='uninstall'

case "$1" in
  "$install")
    cp bin/librefqueue.so ~/.local/lib/
    cp bin/librefqueue.a ~/.local/lib/
    cp include/refqueue.h ~/.local/include
  ;;
  "$uninstall")
    rm ~/.local/lib/librefqueue.so
    rm ~/.local/lib/librefqueue.a
    rm ~/.local/include/refqueue.h
  ;;
  *)
    
  ;;
esac
