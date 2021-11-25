# %%
devtools::load_all()

tick_times <- c(1,3,6,10,11,16,20)
tock_times <- c(3,11,10,12,18,25,26)
tick_names <- c("A", "A", "B", "C", "C", "C", "D")
tock_names <- c("A", "C", "B", "C", "A", "C", "D")

test(tick_names, tock_names, tick_times, tock_times) 
# %%
