set(FONTS
    fonts/quicksand_light.ttf
    fonts/quicksand_book.ttf)

foreach(font ${FONTS})
    file(COPY ${font} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/assets/fonts)
endforeach(font)
