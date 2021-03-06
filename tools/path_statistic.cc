// MIT License

// Copyright (c) 2019 Edward Liu

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <pcl/console/parse.h>
#include <pcl/filters/random_sample.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <iostream>

int main(int argc, char** argv) {
  std::string pcd_filename = "";
  pcl::console::parse_argument(argc, argv, "-pc", pcd_filename);
  if (pcd_filename.empty()) {
    std::cout << "point cloud topic is empty!" << std::endl;
    return -1;
  }

  pcl::PointCloud<pcl::PointXYZI>::Ptr path_cloud(
      new pcl::PointCloud<pcl::PointXYZI>);
  if (pcl::io::loadPCDFile<pcl::PointXYZI>(pcd_filename, *path_cloud) == -1) {
    PCL_ERROR("Couldn't read file\n");
    return (-1);
  }

  std::ofstream path_file("path.csv");
  if (path_file.is_open()) {
    std::ostringstream out;
    for (auto& point : path_cloud->points) {
      out << std::to_string(point.x) << "," << std::to_string(point.y) << ","
          << std::to_string(point.z) << "," << std::to_string(point.intensity)
          << "\n";
    }

    path_file << out.str();
    path_file.close();
  } else {
    PCL_ERROR("Failed to open file.\n");
  }

  return 0;
}
