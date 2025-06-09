def multiple_returns():
    my_dict = {
        "safsad":"dsfasd",
        "fsdfsd":{1,2,4,"sasdas"},
        "fsadfdsfa": [1,2,3,"string"],
        "sdfsadf":(1,2,3,"string"),
        "asfafd": {
            "asfsad": 12312
        }
    }
    return {1,2,"string"},"fuck",True,[1,2,3],(2,3,4,"sadjfal",[1,2,3]), my_dict

x,y,z,w,n,my_dict=multiple_returns()
print(x,y,z,w,n,my_dict)