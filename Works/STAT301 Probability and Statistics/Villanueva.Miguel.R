# Villanueva.Miguel.R
#
# Miguel Villanueva
# Stat-301
# Started:  May 1, 2022
# Finished: May 9, 2022
#
# Extra Credit
#   Problems done:     8/10
#   Questions skipped: 6 and 10
#

# 1)
# === CH 1 Question 5 ===
#   Find population: mean, variance, and standard deviation
#   Take three different samples of size 5
#   Find the sample mean and variance
population1 <- c(10,14,22,0,5,5,11,0,0,0,1,5,22,10)
population1.mean <- mean(population1)
print(population1.mean)
population1.var <- var(population1)
print(population1.var)
population1.sd <- sd(population1)
print(population1.sd)
for(i in 1:3)
{
  s1 <- sample(population1, 5, replace = TRUE)
  s1.mean <- mean(s1)
  s1.var <- var(s1)
  cat("SAMPLE", i, "\n")
  print(s1.mean)
  print(s1.var)
}

# 2)
# === CH 3 Question 3 ===
#   Find the probability that
#     a) exactly three drinkers prefer cola S
#     b) at least three drinkers prefer cola S
#     c) at most one drinker prefers S
dbinom(3,6,0.5)
dbinom(3,6,0.5) + dbinom(4,6,0.5) + dbinom(5,6,0.5) + dbinom(6,6,0.5)
pbinom(1,6,0.5)

# 3)
# === CH 3 Question 4 ===
#   Credit Cards. Find:
#     a) probability distribution of X
#     b) expected value of X
#     c) variance of X
plot(0:10, dbinom(0:10,10,0.75), type='l')
ex1 <- sum(dbinom(0:10,10,0.75)*0:10)
print(ex1)
sum((0:10-ex1)^2*dbinom(0:10,10,0.75))

# 4)
# === CH 4 Question 1 ===
# What is the difference in probability that INCAND will outlast the
# standard light bulb after a total run of 700 hours
p1 <- 1-(pexp(200,0.002))
p2 <- 1-(pexp(200,0.001))
p2 - p1

# 5)
# === CH 4 Question 5 ===
# Determine the probabilities
# P(Z<=2),P(-2<=Z<=2),P(Z>=0)
# P(X<=2),P(X>=3),P(X>=0)
# a)
pnorm(2,0,1)
pnorm(2,0,1)-pnorm(-2,0,1)
1-pnorm(0,0,1)
# b)
pnorm(2,3,4)
1-pnorm(3,3,4)
1-pnorm(0,3,4)

# 6)
# === CH 5 Question 10 ===
# Skip

# 7)
# === CH 6 Question 2 ===
# The population standard deviation is unknown
# Confidence intervals will increase in size due to 
# increasing confidence level
#
# Build a 90%, a 95%, and a 99% interval estimate for mean salary
salaries.sample <- c(44600,30800,55200,34500,4200,52300,22000,12500,18300,62200)
mean1 <- mean(salaries.sample)
sd1 <- sd(salaries.sample)
size1 <- 10
error90 <- qt(0.95,df=size1-1)*sd1/sqrt(size1)
left90 <- mean1-error90
right90 <- mean1+error90
error95 <- qt(0.975,df=size1-1)*sd1/sqrt(size1)
left95 <- mean1-error95
right95 <- mean1+error95
error99 <- qt(0.995,df=size1-1)*sd1/sqrt(size1)
left99 <- mean1-error99
right99 <- mean1+error99
# 90%
sprintf("(%f,%f)",left90,right90)
# 95%
sprintf("(%f,%f)",left95,right95)
# 99%
sprintf("(%f,%f)",left99,right99)

# 8)
# === CH 6 Question 7 ===
# Find the coefficient that is necessary to build a 99.9%
# confidence interval about the population mean
qnorm(1-0.0005)

# 9)
# === CH 7 Question 1 ===
# Sprinkler system hypothesis test
# Does the data contradict the manufacture's claim at significance level 0.01
z.obs <- (131.08-130)/(1.5/sqrt(9))
2*(1-pnorm(z.obs,0,1))
# Answer: there is not sufficient statistical evidence to contradict the claim

# 10)
# === CH 8 Question 2 ===
# Skip
