echo "QMK Docker bootstrapper v0.2.5"

make clean

make clean

(
    # https://stackoverflow.com/a/1407098
    export IFS=","
    for curr_keyboard in $keyboard; do
        for curr_layout in $layout; do
            echo
            echo "================================================================================"
            echo "Building ${curr_keyboard}:${curr_layout}"
            echo "================================================================================"
            echo
            make ${curr_keyboard}:${curr_layout}
            # cp ${curr_keyboard}_${curr_layout}.hex /output/${curr_keyboard}_${curr_layout}.hex
        done
    done

    echo
    echo "================================================================================"
    echo "Copying output"
    echo "================================================================================"
    echo

    for file in *.hex; do
        echo "Copying file $file"
        cp $file /output
    done
)

echo
echo "================================================================================"
echo "Complete"
echo "================================================================================"
echo
