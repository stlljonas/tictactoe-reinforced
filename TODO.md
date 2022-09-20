Add random exploration to LearningAgent
Train until value function updates are negligible (steady state)
Add persistence.
Create multiple different learners. Or add a "RL strategy" to be able to switch it (don't forget to reset internals in that case.


How to implement policy iteration:
2 steps:
    - first we simulate with a **fixed** policy to finc the value function following from the policy. That means given a state, the policy will always give the same action during this time. So either we keep a constant valueFunction to search for actions that lead to states with maximal values, or we compute the optimal states (under the fixed policy) beforehand. How do we find the value function? => brute force all initial states. If a state has already been visited, we don't need to update. The opponent must also act deterministicaly during these simulations.
    - given the value function from the previous step, we can recompute the policy (mapping from state to action) for every state. 
and then repeat the previous steps until convergence. 
    
