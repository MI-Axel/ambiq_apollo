function check_valid_ordering(ordering_str, NUM_MICS)

try
    ordering = eval(ordering_str);
catch err
    rethrow(err)
end

if min(ordering) < 1
    msgbox(sprintf('Ordering indices must be larger than 0!'))
    error('Ordering indices must be larger than 0!')
elseif max(ordering) > NUM_MICS
    msgbox(sprintf('Ordering indices must be smaller than %d!', NUM_MICS))
    error('Ordering indices must be smaller than %d!', NUM_MICS)
elseif length(ordering)~=NUM_MICS
    msgbox(sprintf('Length of ordering must equal %d!', NUM_MICS))
    error('Length of ordering must equal %d!', NUM_MICS)
elseif length(unique(ordering)) < length(ordering)
    msgbox('Cannot have multiple microphones in the same locations!')
    error('Cannot have multiple microphones in the same locations!')
end