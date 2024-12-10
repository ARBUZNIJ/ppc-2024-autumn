#include <gtest/gtest.h>

#include "seq/kovalev_k_multidimensional_integrals_rectangle_method/include/header.hpp"

namespace kovalev_k_multidimensional_integrals_rectangle_method_seq {
const double MY_PI = 3.14159265358979323846;

double area(std::vector<double> &arguments) { return 1.0; }

double f1(std::vector<double> &arguments) { return arguments.at(0); }
double f1cos(std::vector<double> &arguments) { return std::cos(arguments.at(0)); }
double f1Euler(std::vector<double> &arguments) { return 2 * std::cos(arguments.at(0)) * std::sin(arguments.at(0)); }
double f2(std::vector<double> &arguments) { return arguments.at(0) * arguments.at(1); }
double f2advanced(std::vector<double> &arguments) { return std::tan(arguments.at(0)) * std::atan(arguments.at(1)); }
double f3(std::vector<double> &arguments) { return arguments.at(0) * arguments.at(1) * arguments.at(2); }
double f3advanced(std::vector<double> &arguments) {
  return std::sin(arguments.at(0)) * std::tan(arguments.at(1)) * std::log(arguments.at(2));
}
}  // namespace kovalev_k_multidimensional_integrals_rectangle_method_seq

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, zero_length) {
  std::vector<std::pair<double, double>> lims;
  double h = 0.001;
  std::vector<double> out;
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::f1);
  ASSERT_FALSE(tmpTaskSeq.validation());
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, incorrect_output) {
  std::vector<std::pair<double, double>> lims(1);
  double h = 0.001;
  std::vector<double> out(2);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::f1);
  ASSERT_FALSE(tmpTaskSeq.validation());
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, minus_05pi_05pi_cos) {
  const size_t dim = 1;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = -0.5 * kovalev_k_multidimensional_integrals_rectangle_method_seq::MY_PI;
  lims[0].second = 0.5 * kovalev_k_multidimensional_integrals_rectangle_method_seq::MY_PI;
  double h = 0.0005;
  double eps = 1e-4;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::f1cos);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(2.0, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, Eulers_integral) {
  const size_t dim = 1;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = 0;
  lims[0].second = 0.5 * kovalev_k_multidimensional_integrals_rectangle_method_seq::MY_PI;
  double h = 0.0005;
  double eps = 1e-4;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::f1Euler);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(1.0, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, 05x05_area) {
  const size_t dim = 2;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = lims[1].first = 0.0;
  lims[0].second = lims[1].second = 0.5;
  double h = 0.002;
  double eps = 3e-3;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::area);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(0.25, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, 05x05_xy) {
  const size_t dim = 2;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = lims[1].first = 0.0;
  lims[0].second = lims[1].second = 0.5;
  double h = 0.005;
  double eps = 1e-3;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::f2);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(0.015625, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, _0_05x0_05_tg_x_arctan_y) {
  const size_t dim = 2;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = lims[1].first = 0.0;
  lims[0].second = lims[1].second = 0.5;
  double h = 0.001;
  double eps = 1e-3;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::f2advanced);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(0.0157030198483187, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, 2x2_area) {
  const size_t dim = 2;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = lims[1].first = 0.0;
  lims[0].second = lims[1].second = 2.0;
  double h = 0.005;
  double eps = 1e-4;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::area);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(4.0, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, 2_3x1_4_area) {
  const size_t dim = 2;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = 2.0;
  lims[0].second = 3.0;
  lims[1].first = 1.0;
  lims[1].second = 4.0;
  double h = 0.005;
  double eps = 1e-4;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::area);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(3.0, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, _0_2xminus2_0_area) {
  const size_t dim = 2;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = 0.0;
  lims[0].second = 2.0;
  lims[1].first = -2.0;
  lims[1].second = 0.0;
  double h = 0.005;
  double eps = 1e-4;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::area);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(4.0, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, minus1_0xminus1_0_xy) {
  const size_t dim = 2;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = -1.0;
  lims[0].second = 0.0;
  lims[1].first = -1.0;
  lims[1].second = 0.0;
  double h = 0.005;
  double eps = 1e-4;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::f2);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(0.25, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, minus03_0_x_15_17_x_2_21_area) {
  const size_t dim = 3;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = -0.3;
  lims[0].second = 0.0;
  lims[1].first = 1.5;
  lims[1].second = 1.7;
  lims[2].first = 2.0;
  lims[2].second = 2.1;
  double h = 0.005;
  double eps = 1e-4;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::area);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(0.006, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, 08_1_x_15_17_x_18_2_xyz) {
  const size_t dim = 3;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = 0.8;
  lims[0].second = 1.0;
  lims[1].first = 1.5;
  lims[1].second = 1.7;
  lims[2].first = 1.8;
  lims[2].second = 2.0;
  double h = 0.005;
  double eps = 1e-3;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::f3);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(0.021888, out[0], eps);
}

TEST(kovalev_k_multidimensional_integrals_rectangle_method_seq, 08_1_x_19_2_x_29_3_sinx_tgy_lnz) {
  const size_t dim = 3;
  std::vector<std::pair<double, double>> lims(dim);
  lims[0].first = 0.8;
  lims[0].second = 1.0;
  lims[1].first = 1.9;
  lims[1].second = 2.0;
  lims[2].first = 2.9;
  lims[2].second = 3.0;
  double h = 0.005;
  double eps = 1e-3;
  std::vector<double> out(1);
  std::shared_ptr<ppc::core::TaskData> taskSeq = std::make_shared<ppc::core::TaskData>();
  taskSeq->inputs_count.emplace_back(lims.size());
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lims.data()));
  taskSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&h));
  taskSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskSeq->outputs_count.emplace_back(out.size());
  kovalev_k_multidimensional_integrals_rectangle_method_seq::MultidimensionalIntegralsRectangleMethod tmpTaskSeq(
      taskSeq, kovalev_k_multidimensional_integrals_rectangle_method_seq::f3advanced);
  ASSERT_TRUE(tmpTaskSeq.validation());
  tmpTaskSeq.pre_processing();
  tmpTaskSeq.run();
  tmpTaskSeq.post_processing();
  ASSERT_NEAR(-0.00427191467841401, out[0], eps);
}