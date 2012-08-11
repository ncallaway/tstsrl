set(ASSETS
    fonts/quicksand_light.ttf
    fonts/quicksand_book.ttf)

foreach(asset ${ASSETS})
    file(COPY ${asset} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/assets)
endforeach(asset)
