int mechanicalAccumulator(int target) {
    
    if(target==0)
    return 0;
    else
    return mechanicalAccumulator(target-1)+target;
}
