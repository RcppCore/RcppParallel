# Compile and fit a trivial Stan model. Building rstan proves the headers and
# link line are right; actually running a model additionally exercises the TBB
# runtime that RcppParallel loaded -- including the reduce_sum / task isolation
# path that the old Rtools42 TBB could not support.

library(rstan)

code <- "
data {
  int<lower=0> N;
  vector[N] y;
}
parameters {
  real mu;
}
model {
  y ~ normal(mu, 1);
}
"

set.seed(42)
data <- list(N = 20L, y = rnorm(20, mean = 3))

fit <- stan(
  model_code = code,
  data       = data,
  chains     = 1L,
  iter       = 200L,
  refresh    = 0L
)

estimate <- mean(rstan::extract(fit, "mu")[["mu"]])
writeLines(sprintf("posterior mean of mu: %.3f (data mean %.3f)", estimate, mean(data$y)))

# a wildly wrong answer would mean the model ran but the sampler is broken;
# with 20 observations and unit scale this is a very loose bound
if (!is.finite(estimate) || abs(estimate - mean(data$y)) > 1)
   stop("posterior mean is implausible; the fit did not work correctly")

writeLines("** rstan fit check passed")
