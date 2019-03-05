echo "QMK Docker bootstrapper v0.2.4"

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
            cp ${curr_keyboard}_${curr_layout}.hex /output/${curr_keyboard}_${curr_layout}.hex
        done
    done
)

echo "Complete"
