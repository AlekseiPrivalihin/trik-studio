ARRAY8 @@RANDOM_ID_1@@ 4
ARRAY(CREATE8, 4, @@RANDOM_ID_1@@)
ARRAY(INIT8, @@RANDOM_ID_1@@, 0, 3, 1, 65, 67)

ARRAY8 @@RANDOM_ID_2@@ 4
ARRAY(CREATE8, 4, @@RANDOM_ID_2@@)
ARRAY(INIT8, @@RANDOM_ID_2@@, 0,4,1,1,1,1)

INPUT_DEVICE(SETUP, 0, @@PORT@@, 1, 0, 3, @@@RANDOM_ID_1@@, 0, @@@RANDOM_ID_2@@)
ARRAY(DELETE, @@RANDOM_ID_1@@)
ARRAY(DELETE, @@RANDOM_ID_2@@)