CC = g++
CFLAGS = -std=c++20 -I./inc -Wall `wx-config --cxxflags` -I/usr/local/opt/opencv/include/opencv4
LDFLAGS = -L/usr/local/opt/opencv/lib -lsfml-graphics -lsfml-window -lsfml-system `wx-config --libs` \
-lopencv_gapi -lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect \
-lopencv_dnn_superres -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform \
-lopencv_line_descriptor -lopencv_mcc -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_signal \
-lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking \
-lopencv_highgui -lopencv_datasets -lopencv_text -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_wechat_qrcode \
-lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d \
-lopencv_imgcodecs -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=out/%.o)
TARGET = app

# Default target to build the application
all: $(TARGET)

# Link the object files into the final target
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile the source files into object files
out/%.o: src/%.cpp
	mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the generated files
clean:
	rm -rf out $(TARGET)
