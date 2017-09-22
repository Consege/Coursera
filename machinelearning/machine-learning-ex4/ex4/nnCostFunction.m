function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%

%part 1

%加入偏置项,计算输出层的值
a1 = [ones(m,1),X];
z1 = a1*Theta1';
a2  =sigmoid(z1);

a2 = [ones(m,1),a2];

z2 = a2*Theta2';
a3 = sigmoid(z2);
%计算cost
Y = eye(num_labels);
Y = Y(y,:);
cost = sum((-Y .* log(a3)) - ((1 - Y) .* log(1 - a3)), 2);%先求矩阵每一行的和，即1~K的和
J = sum(cost)/m ;

%正则化
Theta1NoBias = Theta1(:,2:end);
Theta2NoBias = Theta2(:,2:end);

reg  = (lambda / (2 * m)) * (sum(Theta1NoBias(:).*Theta1NoBias(:)) + sum(Theta2NoBias(:).*Theta2NoBias(:)));
J = J+reg;



%计算梯度
Delta1 = 0 ;
Delta2 = 0 ;

for t = 1:m
    a1t = a1(t,:);
    z2t = a1t*Theta1';
    a2t = [1,sigmoid(z2t)];
    z3t = a2t*Theta2' ;
    a3t = sigmoid(z3t) ;
    
    delta3 = a3t - Y(t,:) ;
    delta2 = (delta3*Theta2NoBias).*sigmoidGradient(z2t);
    %size(delta3)
    %size(a2t)
    Delta2 = Delta2 + ( a2t' * delta3 );
	Delta1 = Delta1 + ( a1t' * delta2 );
end
Theta1_grad = (1 / m) * Delta1;
Theta2_grad  = (1 / m) * Delta2 ;

Theta1_grad = Theta1_grad' ;
Theta2_grad = Theta2_grad' ;
Theta1_grad(:, 2:end) =Theta1_grad(:, 2:end) + (lambda / m) * Theta1NoBias;
Theta2_grad(:, 2:end) =Theta2_grad(:, 2:end) + (lambda / m) * Theta2NoBias;
 
    
    













% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
