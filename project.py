
from pathlib import Path
from numpy import array
import numpy as np
from keras import optimizers
from keras.optimizers import RMSprop
from keras.utils.vis_utils import plot_model
from keras.models import Model
from keras.layers import Input
from keras.layers import Dense
from keras.layers import Flatten
from keras.layers import Dropout
from keras.layers import Embedding
from keras.layers import Reshape
from keras.layers import ZeroPadding2D
from keras.layers import Masking
from keras.models import Sequential
from keras.layers import  Activation
from keras.layers import Add
from keras.layers.convolutional import Conv2D
from keras.layers.convolutional import MaxPooling2D
from keras.layers.merge import concatenate
from keras import backend as K
import re
import operator
import math 
from itertools import islice
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
import itertools
from random import randint
# global variables
AUTHORS = {}
# this is filter values for conv2D layers
k1_gram = 2
k2_gram = 3
k3_gram = 5

# sample with padding
GramThreshold = 150
# always use a square value
# taken top most
InputThreshold = 121
# defines the nodes in output layer
OutputThreshold = 0

def sensitivity(y_true, y_pred):
    true_positives = K.sum(K.round(K.clip(y_true * y_pred, 0, 1)))
    possible_positives = K.sum(K.round(K.clip(y_true, 0, 1)))
    return true_positives / (possible_positives + K.epsilon())

def specificity(y_true, y_pred):
    true_negatives = K.sum(K.round(K.clip((1-y_true) * (1-y_pred), 0, 1)))
    possible_negatives = K.sum(K.round(K.clip(1-y_true, 0, 1)))
    return true_negatives / (possible_negatives + K.epsilon())

 
def take(n, iterable):
    all_tokens = list(islice(iterable, n))
#   3all_tokens = all_tokens[10:]
    return all_tokens
def encode_text_error(lines, length=0) :
    if length == 0:
        length = InputThreshold
    _token_dict = {}
    tokenizer = []
    for i in range(len(lines)):
        codeToken = re.findall(r"[\w]+|[_.,!?;:=-><'\"/)(\[\]#@\s]", lines[i])
        for j in range(len(codeToken)):
            if codeToken[j] not in _token_dict:
                _token_dict[codeToken[j]] = 1
                #tokenizer[i][j] = _token_dict[codeToken[j]]
            else:
              _token_dict[codeToken[j]] = _token_dict[codeToken[j]] + 1 
    sorted_token_dict = dict( sorted(_token_dict.items(), key=operator.itemgetter(1),reverse=True))
    n_items = take(GramThreshold, sorted_token_dict.items())              
    _token_dict  = dict(n_items)
    token_list = list(_token_dict.keys())
    
    for idx in range(len(token_list )):
        _token_dict[token_list[idx]] = {'value': str(idx + 1)}
    print(_token_dict)
    for i in range(len(lines)):
        codeToken = re.findall(r"[\w]+|[_.,!?;:=-><'\"/)(\[\]#@\s]", lines[i])
        token = ['0' for k in range(length)]
        for j in range(len(codeToken)):
            if codeToken[j] in _token_dict and j < length:
                token[j] = _token_dict[codeToken[j]]['value']
        tokenizer.append(token)
    print(_token_dict)
    return tokenizer, len(_token_dict.keys())

def encode_label_error(Y):
    output = []
    authors = []
    for y in Y:
        if y not in authors:
            authors.append(y)
        output.append([authors.index(y)])
    return output

def Metrices(y_actual, y_predict):
    TP = [0, 0,0,0]
    FP = [0, 0,0,0]
    TN = [0, 0,0,0]
    FN = [0, 0,0,0]

    for j in range(len(y_predict)): 
        actual = y_actual[j]
        predict = y_predict[j]
        for i in range(len(actual)):
            if actual[i]==predict[i]==1:
               TP[i] += 1
            if predict[i]==1 and actual[i]!=predict[i]:
               FP[i] += 1
            if actual[i]==predict[i]==0:
               TN[i] += 1
            if predict[i]==0 and actual[i]!=predict[i]:
               FN[i] += 1
    TP = sum(TP)
    FN  = sum(FN )
    FP = sum(FP)
    TN = sum(TN)
    return(TP, FP, TN, FN)
# encode a list of lines
def encode_label(lines):
    rows = len(lines)
    _token_dict = {}
    length = OutputThreshold 
    next_num = 0
    tokenizer = []
    for author in lines:
        if author not in _token_dict:
            _token_dict[author] = next_num
            next_num += 1
            
    for i in range(rows):
        row = [0 for j in range(length)]
        row[_token_dict[lines[i]]] = 1
        tokenizer.append(row)
    return tokenizer, len(_token_dict.keys())


def encode_text(lines, length=0):
    rows = len(lines)
    if length == 0:
        length = InputThreshold
    _token_dict = {}
    tokenizer = [['0' for i in range(length)] for j in range(rows)]
    for i in range(len(lines)):
        codeToken = re.findall(r"[\w]+|[_.,!?;:=-><'\"/)(\[\]#@\s]", lines[i])
        for j in range(len(codeToken)):
            if codeToken[j] not in _token_dict:
                _token_dict[codeToken[j]] = 1
            else:
              _token_dict[codeToken[j]] = _token_dict[codeToken[j]] + 1 
    sorted_token_dict = dict( sorted(_token_dict.items(), key=operator.itemgetter(1),reverse=True))
    if len(sorted_token_dict.keys()) < GramThreshold:
        print("insufficient dataset")
        return [], 0
    n_items = take(GramThreshold, sorted_token_dict.items())              
    _token_dict  = dict(n_items)
    token_list = list(_token_dict.keys())
    
    for idx in range(len(token_list )):
        _token_dict[token_list[idx]] = {'value': str(idx + 1)}
    print(_token_dict)
    for i in range(len(lines)):
        codeToken = re.findall(r"[\w]+|[_.,!?;:=-><'\"/)(\[\]#@\s]", lines[i])
        for j in range(len(codeToken)):
            if codeToken[j] in _token_dict and j < length:
                tokenizer[i][j] = _token_dict[codeToken[j]]['value']
    print(_token_dict)
    return tokenizer, len(_token_dict.keys())

def reshapeInput(X, input_dim):
    dim1 = X.shape[0]
    G = np.reshape(X, (dim1, input_dim, input_dim))
    return G
   
# model for authorship prediction
def definedModel(length, vocab_size):
	# channel 1
    global k1_gram
    global k2_gram
    global k3_gram
    activation = 'sigmoid'
    activation2 = 'relu'
    embedding_size = 30#50
    dropout_amount = 0.3 #0.1
    # channel with kernel 2x2
    inputs1 = Input(shape=(length,length, ), name = '0CONV2D')
    embedding1 = Embedding(vocab_size, embedding_size, name = '1CONV2D')(inputs1)
    conv1 = Conv2D(32, k1_gram, k1_gram, activation=activation, name = '2CONV2D')(embedding1)
    conv1b = Conv2D(32, k1_gram, k1_gram, activation=activation, name = '3CONV2D')(conv1)
    pool1b = MaxPooling2D(pool_size=(2,2), strides=(2, 2), name = '4CONV2D')(conv1b)
    drop1b = Dropout(dropout_amount, name = '5CONV2D')(pool1b)
    flat1 = Flatten(name = '6CONV2D')(drop1b)

    # channel with kernel 3x3
    inputs2 = Input(shape=(length,length, ), name = '7CONV2D')
    embedding2 = Embedding(vocab_size, embedding_size, name = '8CONV2D')(inputs2)
    conv2 = Conv2D(32,  (k2_gram, k2_gram), strides=(2, 2), activation=activation, name = '9CONV2D')(embedding2)
    padding2 = ZeroPadding2D((2, 2), name = '10CONV2D')(conv2)
    conv2b = Conv2D(32,  (k2_gram, k2_gram),strides=(2, 2), activation=activation, name = '11CONV2D')(padding2)
    pool2 = MaxPooling2D(pool_size= (2,2), strides=(2, 2), name = '12CONV2D')(conv2b)
    drop2b = Dropout(dropout_amount , name = '13CONV2D')(pool2)
    flat2 = Flatten(name = '14CONV2D')(drop2b)
#
#    # channel with kernel 4x4
    inputs3 = Input(shape=(length,length,), name = '15CONV2D')
    embedding3 = Embedding(vocab_size, embedding_size, name = '16CONV2D')(inputs3)
    conv3 = Conv2D(16, (k3_gram, k3_gram ), strides=(2, 2), activation=activation, name = '17CONV2D')(embedding3)
    padding3 = ZeroPadding2D((3, 3), name = '18CONV2D')(conv3)
    conv3b = Conv2D(16, (k3_gram, k3_gram ), strides=(2, 2), activation=activation, name = '19CONV2D')(padding3)
    pool3 = MaxPooling2D(pool_size=(2,2), strides=(2, 2), name = '20CONV2D')(conv3b)
    drop3 = Dropout(dropout_amount, name = '21CONV2D')(pool3)
    flat3 = Flatten(name = '22CONV2D')(drop3)

    merged = concatenate([flat1, flat2, flat3], name = '23CONV2D')
    dense2 = Dense(OutputThreshold * 3, activation=activation2, name = '24CONV2D')(merged)
#    dense2 = Dense(OutputThreshold * 3, activation=activation2, name = '24CONV2D')(flat3)
    outputs = Dense(OutputThreshold, activation=activation, name = '25CONV2D')(dense2)
    model = Model(inputs=[inputs1, inputs2, inputs3], outputs=outputs)
    Nadam = optimizers.Nadam(lr=0.002)    
    model.compile(loss='binary_crossentropy', optimizer=Nadam, metrics=[sensitivity, specificity, 'accuracy'])
    print(model.summary())
    plot_model(model, show_shapes=True, to_file='authorship_model.png')
    return model

def Finalmodel(length,cols, vocab_size):
	# channel 1
    k3_gram = 5
    activation = 'sigmoid'
    activation2 = 'relu'
    embedding_size = 50#50
    dropout_amount = 0.2 #0.1
    # channel with kernel 2x2
    cols = length + cols
    inputs1 = Input(shape=(length,cols, ), name = '0CONV2D')
    embedding1 = Embedding(vocab_size, embedding_size, name = '1CONV2D')(inputs1)
    conv1 = Conv2D(32, k1_gram, k1_gram, activation=activation, name = '2CONV2D')(embedding1)
    conv1b = Conv2D(32, k1_gram, k1_gram, activation=activation, name = '3CONV2D')(conv1)
    pool1b = MaxPooling2D(pool_size=(2,2), strides=(2, 2), name = '4CONV2D')(conv1b)
    drop1b = Dropout(dropout_amount, name = '5CONV2D')(pool1b)
    flat1 = Flatten(name = '6CONV2D')(drop1b)

    # channel with kernel 3x3
    inputs2 = Input(shape=(length,cols, ), name = '7CONV2D')
    embedding2 = Embedding(vocab_size, embedding_size, name = '8CONV2D')(inputs2)
    conv2 = Conv2D(32,  (k2_gram, k2_gram), strides=(2, 2), activation=activation, name = '9CONV2D')(embedding2)
    padding2 = ZeroPadding2D((2, 2), name = '10CONV2D')(conv2)
    conv2b = Conv2D(32,  (k2_gram, k2_gram),strides=(2, 2), activation=activation, name = '11CONV2D')(padding2)
    pool2 = MaxPooling2D(pool_size= (2,2), strides=(2, 2), name = '12CONV2D')(conv2b)
    drop2b = Dropout(dropout_amount , name = '13CONV2D')(pool2)
    flat2 = Flatten(name = '14CONV2D')(drop2b)
    
    inputs3 = Input(shape=(length,cols,), name = '15CONV2D')
    embedding3 = Embedding(vocab_size, embedding_size, name = '16CONV2D')(inputs3)
    conv3 = Conv2D(32, (k3_gram, k3_gram ), strides=(2, 2), activation=activation, name = '17CONV2D')(embedding3)
    padding3 = ZeroPadding2D((3, 3), name = '18CONV2D')(conv3)
    conv3b = Conv2D(32, (k3_gram, k3_gram ), strides=(2, 2), activation=activation, name = '19CONV2D')(padding3)
    pool3 = MaxPooling2D(pool_size=(2,2), strides=(2, 2), name = '20CONV2D')(conv3b)
    drop3 = Dropout(dropout_amount, name = '21CONV2D')(pool3)
    flat3 = Flatten(name = '22CONV2D')(drop3)
#    
    merged = concatenate([flat1, flat2, flat3], name = '23CONV2D')
    dense2 = Dense(10, activation=activation2, name = '24CONV2D')(merged)
    outputs = Dense(1, activation=activation, name = '25CONV2D')(dense2)
    model = Model(inputs=[inputs1, inputs2, inputs3], outputs=outputs)
    Nadam = optimizers.Nadam(lr=0.002)    
    model.compile(loss='binary_crossentropy', optimizer=Nadam, metrics=[sensitivity, specificity, 'accuracy'])
    print(model.summary())
    plot_model(model, show_shapes=True, to_file='error_predict_model.png')
    return model

def plot_confusion_matrix(cm,
                         classes,
                         normalize=False,
                         title='Confusion Matrix',
                         cmap=plt.cm.Blues):
    
    plt.imshow(cm, interpolation='nearest', cmap=cmap)
    plt.title(title)
    plt.colorbar()
    tick_marks = np.arange(len(classes))
    plt.xticks(tick_marks, classes, rotation=45)
    plt.yticks(tick_marks, classes)
    
    if normalize:
        cm = cm.astype('float') / cm.sum(axis=1)[:,np.newaxis]
        print("Normalized confusion matrix")
    else:
        print("Confusion Matrix without normalization")
        
    thresh = cm.max() / 2
    for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        plt.text(j, i, cm[i, j],
                horizontalalignment = "center",
                color = "white" if cm[i,j]> thresh else "black")
    plt.tight_layout()
    plt.ylabel('True label')
    plt.xlabel('Predicted label')
    plt.show()

def loadData():
	# please change the path
    directory = "code jam/"
    pathlist = Path(directory).glob('*/*.cpp')
    global OutputThreshold
    for path in pathlist:
        path_in_str = str(path)
        author = path_in_str.split('\\')[-2]
        if author not in AUTHORS:
            AUTHORS[author] = []
        print(path_in_str)
        file = open(path_in_str)
        sam = file.readlines()
        for s in sam:
                AUTHORS[author].append(s)
    X = []
    Y = []
    for author, data in AUTHORS.items():
      for line in data:
          X.append(line)
          Y.append(author)
    OutputThreshold = len(AUTHORS.keys())
    return X, Y


def processData(X, Y, input_dim, error=False):
    if not error:
        X_train_processed, X_vocab_size_train = encode_text(X) # [[]]
        X_train_processed = np.array(X_train_processed)
        X_train_processed = reshapeInput(X_train_processed, input_dim)        
        Y_train_processed, Y_vocab_size_train = encode_label(Y) # [[]]
        return X_train_processed, Y_train_processed, X_vocab_size_train
    else:
        X_train_processed, X_vocab_size_train = encode_text_error(X) # [[]]
        Y_train_processed = encode_label_error(Y)
        return X_train_processed, Y_train_processed, X_vocab_size_train


def main():
    # getting input
    input_dim = int(math.sqrt(InputThreshold))
    X_train_def, Y_train_def = loadData()    
    X_train, Y_train, vocab_size = processData(X_train_def , Y_train_def , input_dim)
    Y_error = []
    for i in range(len(X_train)):
        author =  Y_train[i]
        if author[0] == 1 and randint(0,10) <= 7:
            Y_error.append([1])
        else:
            Y_error.append([0])

    ## first model for authorship

    model1 = definedModel(input_dim, vocab_size + 1)    
    model1.fit([X_train, X_train, X_train], array(Y_train), epochs=100, batch_size=32,validation_split=0.2)
    
    history = model1.evaluate([X_train, X_train,X_train], array(Y_train))
    predict_author = model1.predict([X_train, X_train,X_train])
    predicted_author = []
    for predict in predict_author:
        l = max(predict)
        idx = list(predict).index(l)
        p = [0] * OutputThreshold
        p[idx] = 1
        predicted_author.append(p)

    TP, FP, TN, FN = Metrices(Y_train, predicted_author)
    PPV = TP / (TP + FP)
    NPV = TN / (TN + FN)
    print("PPV:", round(PPV, 2) )
    print("NPV:", round(NPV, 2))
    

    X_error = []
    for i in range(len(X_train)):
        author = predicted_author[i]
        code  = list(X_train[i])
        for j in range(len(code)):
            code[j] = list(code[j]) + author
        X_error.append(code)    
        
    # 2nd model for error prediction
    model2 = Finalmodel(input_dim , OutputThreshold, vocab_size + 2)    
    model2.fit([X_error,X_error,X_error], array(Y_error), epochs=100, batch_size=32,validation_split=0.1)
    predict_error = model2.predict([X_error,X_error,X_error])
    
    predicted_error = [int(round(x[0])) for x in predict_error]
    Y_train_error = [round(x[0]) for x in Y_error]
    cm = confusion_matrix(Y_train_error, predicted_error)
    cm_plot_labels = ['correct', 'error']
    plot_confusion_matrix(cm, cm_plot_labels, title='Confusion Matrix')


if __name__  == "__main__":
    main()


