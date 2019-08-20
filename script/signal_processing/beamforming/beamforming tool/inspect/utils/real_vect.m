function [ real_x ] = real_vect( x )
% real_vect Place real and imaginary components of a vector into a single
% array of length 2*length(x).

x = x(:);
rx = real(x)';
ix = imag(x)';
real_x = reshape([rx;ix],1,[]);

end

