# Introduction
Authorship prediction and stylometric analysis were originally introduced for text documents and literature. It has gained popularity as stylometric analysis can identify the author and their signature and hence can uniquely associate documents, text or literature with their authors. We focus on a very specific field of computer science for authorship prediction which is identifying the authors of the source code. Source code can be written in any programming language and for our implementation, we need the source code in the same programming language for all the authors. Previous studies have proposed many solutions involving feature extraction using the N-gram approach which turns out to yield the best results. This N-gram dataset is fed to neural network architecture (LSTM or convolutional) to predict the author. For the LSTM-based network, training is slow considering we will require quite a large dataset. Whereas 1-Dimensional convolutional neural networks are used with a kernel size of 2 in many other cases. Despite the satisfactory result of previous studies what they lack is the tokens used for feature selection or the N-gram selection. In most of the cases, special characters are often ignored, space and tab chars are removed and trailing white spaces and new line characters are often truncated. In our implementation, we will consider these tokens. Another aspect of our study is to identify the errors made by authors in a programming language. Studies in this area are mostly on syntactical errors and some on the single token syntax errors.

## Token Generation
In our implementation, we consider all the characters that are present in source code. An argument can be made that given a particular programming language there will be many similar tokens, also some Ide's have certain configuration for many languages. We can answer these questions by taking positions of the token into account and giving equal weight to all the tokens. We take 150 top tokens and all tokens are given equal priority therefore even though there are similarities at the same position such cases will be less.
Another major aspect that we touch is the indentation and new line character used by developers and programmers. Many programmers often prefer to start new statement on a new line that produces a new line character at the end of each statement, similarly for languages like C++ and C semi-colon characters are the end of the statement, thus token generated by semi-colon character is important for our implementation of stylometric analysis.


## MULTI-LAYER CONVOLUTIONAL LAYER
The problem can be visualized as detecting the signature of an image. For example, consider images of 2 different persons with the same background, we can say that the signature generated is different because of the 2 persons but not because of the background.
We use a 2-Dimensional Convolutional neural network for this purpose. 
Till now it seems like we have solved the problem but the accuracy that we get is around 87% (with kernel size 2x2 of the convolutional layer). Obviously, because the window size is small we are not taking enough tokens together for analysis. But this does not mean we can ignore smaller parts of the matrix.
Therefore we introduce 2 strategies here, one layer with a smaller scope which concentrates on the limited part of the dataset to understand the relationship between the tokens which are close enough to each other and other with large window size to retain the relationship between the tokens that are further away from each other. 
These 2 strategies can be implemented using a variable kernel size of 2x2, 3x3 and 5x5. Therefore in our implementation, we have used the above-mentioned kernel sizes in 3 different channels. These 3 channels merge into one channel to generate the output which is the author label. We observed that with one channel of kernel size 2x2 we get an accuracy of around 87% whereas if use another channel with a kernel size of 3x3 accuracy increases to 90%. Adding one more channel of 5x5 kernel size increases the accuracy to 90.98%.
On top of this, we use 'Nadam' optimizer for our network as it provides momentum as an in-build functionality. The above-mentioned accuracies are observed with optimizer 'Adam'. With 'Nadam' our overall accuracy jumps to 94%.

## Error Dectection
To address this problem we use the same architecture as above. But we change our input dataset. We add author bits with each input matrix to associate the author with each line of code. Labels, in this case, would the 0 or 1 (error or no-error). The idea behind this is to associate each author with the error they make. We divide our dataset into testing and training with the split of 1:9.

## Limitations
After several rounds of testing, it was found that if we increase the number of authors and their data samples our network starts performing poorly. The optimal number of authors would be a value of less than 10. For future updates, we can try building a deeper channel for our network as the variables increase drastically when we increase the number of authors and their source code sample.
