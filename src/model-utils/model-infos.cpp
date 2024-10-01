#include "model-downloader-types.h"

std::map<std::string, ModelInfo> models_info = {{
	{"M2M-100 418M (495Mb)",
	 {"M2M-100 418M",
	  "m2m-100-418M",
	  MODEL_TYPE_TRANSLATION,
	  {{"https://huggingface.co/jncraton/m2m100_418M-ct2-int8/resolve/main/model.bin?download=true",
	    "D6703DD9F920FF896E45C3D97B490761BED5944937B90BBE6A7245F5652542D4"},
	   {
		   "https://huggingface.co/jncraton/m2m100_418M-ct2-int8/resolve/main/config.json?download=true",
		   "4244772990E30069563E3DDFB4AD6DC95BDFD2AC3DE667EA8858C9B0A8433FA8",
	   },
	   {"https://huggingface.co/jncraton/m2m100_418M-ct2-int8/resolve/main/generation_config.json?download=true",
	    "AED76366507333DDBB8BD49960F23C82FE6446B3319A46A54BEFDB45324CCF61"},
	   {"https://huggingface.co/jncraton/m2m100_418M-ct2-int8/resolve/main/shared_vocabulary.json?download=true",
	    "7EB5D0FF184C6095C7C10F9911C0AEA492250ABD12854F9C3D787C64B1C6397E"},
	   {"https://huggingface.co/jncraton/m2m100_418M-ct2-int8/resolve/main/special_tokens_map.json?download=true",
	    "C1A4F86C3874D279AE1B2A05162858DB5DD6C61665D84223ED886CBCFF08FDA6"},
	   {"https://huggingface.co/jncraton/m2m100_418M-ct2-int8/resolve/main/tokenizer_config.json?download=true",
	    "AE54F15F0649BB05041CDADAD8485BA1FAF40BC33E6B4C2A74AE2D1AE5710FA2"},
	   {"https://huggingface.co/jncraton/m2m100_418M-ct2-int8/resolve/main/vocab.json?download=true",
	    "B6E77E474AEEA8F441363ACA7614317C06381F3EACFE10FB9856D5081D1074CC"},
	   {"https://huggingface.co/jncraton/m2m100_418M-ct2-int8/resolve/main/sentencepiece.bpe.model?download=true",
	    "D8F7C76ED2A5E0822BE39F0A4F95A55EB19C78F4593CE609E2EDBC2AEA4D380A"}}}},
	{"M2M-100 1.2B (1.25Gb)",
	 {"M2M-100 1.2BM",
	  "m2m-100-1_2B",
	  MODEL_TYPE_TRANSLATION,
	  {{"https://huggingface.co/jncraton/m2m100_1.2B-ct2-int8/resolve/main/model.bin?download=true",
	    "C97DF052A558895317312470E1FF7CB8EAE5416F7AE16214A2983C6853DD3CE5"},
	   {
		   "https://huggingface.co/jncraton/m2m100_1.2B-ct2-int8/resolve/main/config.json?download=true",
		   "4244772990E30069563E3DDFB4AD6DC95BDFD2AC3DE667EA8858C9B0A8433FA8",
	   },
	   {"https://huggingface.co/jncraton/m2m100_1.2B-ct2-int8/resolve/main/generation_config.json?download=true",
	    "AED76366507333DDBB8BD49960F23C82FE6446B3319A46A54BEFDB45324CCF61"},
	   {"https://huggingface.co/jncraton/m2m100_1.2B-ct2-int8/resolve/main/shared_vocabulary.json?download=true",
	    "7EB5D0FF184C6095C7C10F9911C0AEA492250ABD12854F9C3D787C64B1C6397E"},
	   {"https://huggingface.co/jncraton/m2m100_1.2B-ct2-int8/resolve/main/special_tokens_map.json?download=true",
	    "C1A4F86C3874D279AE1B2A05162858DB5DD6C61665D84223ED886CBCFF08FDA6"},
	   {"https://huggingface.co/jncraton/m2m100_1.2B-ct2-int8/resolve/main/tokenizer_config.json?download=true",
	    "1566A6CFA4F541A55594C9D5E090F530812D5DE7C94882EA3AF156962D9933AE"},
	   {"https://huggingface.co/jncraton/m2m100_1.2B-ct2-int8/resolve/main/vocab.json?download=true",
	    "B6E77E474AEEA8F441363ACA7614317C06381F3EACFE10FB9856D5081D1074CC"},
	   {"https://huggingface.co/jncraton/m2m100_1.2B-ct2-int8/resolve/main/sentencepiece.bpe.model?download=true",
	    "D8F7C76ED2A5E0822BE39F0A4F95A55EB19C78F4593CE609E2EDBC2AEA4D380A"}}}},
	{"NLLB 200 1.3B (1.4Gb)",
	 {"NLLB 200 1.3B",
	  "nllb-200-1.3b",
	  MODEL_TYPE_TRANSLATION,
	  {{"https://huggingface.co/JustFrederik/nllb-200-distilled-1.3B-ct2-int8/resolve/main/model.bin?download=true",
	    "72D7533DC7A0E8F10F19A650D4E90FAF9CBFA899DB5411AD124BD5802BD91263"},
	   {
		   "https://huggingface.co/JustFrederik/nllb-200-distilled-1.3B-ct2-int8/resolve/main/config.json?download=true",
		   "0C2F6FA2057C7264D052FB4A62BA3476EEAE70487ACDDFA8E779A53A00CBF44C",
	   },
	   {"https://huggingface.co/JustFrederik/nllb-200-distilled-1.3B-ct2-int8/resolve/main/tokenizer.json?download=true",
	    "E316B82DE11D0F951F370943B3C438311629547285129B0B81DADABD01BCA665"},
	   {"https://huggingface.co/JustFrederik/nllb-200-distilled-1.3B-ct2-int8/resolve/main/shared_vocabulary.txt?download=true",
	    "A132A83330F45514C2476EB81D1D69B3C41762264D16CE0A7EA982E5D6C728E5"},
	   {"https://huggingface.co/JustFrederik/nllb-200-distilled-1.3B-ct2-int8/resolve/main/special_tokens_map.json?download=true",
	    "992BD4ED610D644D6823081937BCC91BB8878DD556CEA4AE5327F2480361330E"},
	   {"https://huggingface.co/JustFrederik/nllb-200-distilled-1.3B-ct2-int8/resolve/main/tokenizer_config.json?download=true",
	    "D1AA8C3697D3E35674F97B5B7E9C99D22B010F528E80140257D97316BE90D044"},
	   {"https://huggingface.co/JustFrederik/nllb-200-distilled-1.3B-ct2-int8/resolve/main/sentencepiece.bpe.model?download=true",
	    "14BB8DFB35C0FFDEA7BC01E56CEA38B9E3D5EFCDCB9C251D6B40538E1AAB555A"}}}},
	{"NLLB 200 600M (650Mb)",
	 {"NLLB 200 600M",
	  "nllb-200-600m",
	  MODEL_TYPE_TRANSLATION,
	  {{"https://huggingface.co/JustFrederik/nllb-200-distilled-600M-ct2-int8/resolve/main/model.bin?download=true",
	    "ED1BEAF75134DE7505315A5223162F56ACFF397EFF6B50638A500D3936FE707B"},
	   {
		   "https://huggingface.co/JustFrederik/nllb-200-distilled-600M-ct2-int8/resolve/main/config.json?download=true",
		   "0C2F6FA2057C7264D052FB4A62BA3476EEAE70487ACDDFA8E779A53A00CBF44C",
	   },
	   {"https://huggingface.co/JustFrederik/nllb-200-distilled-600M-ct2-int8/resolve/main/tokenizer.json?download=true",
	    "E316B82DE11D0F951F370943B3C438311629547285129B0B81DADABD01BCA665"},
	   {"https://huggingface.co/JustFrederik/nllb-200-distilled-600M-ct2-int8/resolve/main/shared_vocabulary.txt?download=true",
	    "A132A83330F45514C2476EB81D1D69B3C41762264D16CE0A7EA982E5D6C728E5"},
	   {"https://huggingface.co/JustFrederik/nllb-200-distilled-600M-ct2-int8/resolve/main/special_tokens_map.json?download=true",
	    "992BD4ED610D644D6823081937BCC91BB8878DD556CEA4AE5327F2480361330E"},
	   {"https://huggingface.co/JustFrederik/nllb-200-distilled-600M-ct2-int8/resolve/main/tokenizer_config.json?download=true",
	    "D1AA8C3697D3E35674F97B5B7E9C99D22B010F528E80140257D97316BE90D044"},
	   {"https://huggingface.co/JustFrederik/nllb-200-distilled-600M-ct2-int8/resolve/main/sentencepiece.bpe.model?download=true",
	    "14BB8DFB35C0FFDEA7BC01E56CEA38B9E3D5EFCDCB9C251D6B40538E1AAB555A"}}}},
	{"MADLAD 400 3B (2.9Gb)",
	 {"MADLAD 400 3B",
	  "madlad-400-3b",
	  MODEL_TYPE_TRANSLATION,
	  {{"https://huggingface.co/santhosh/madlad400-3b-ct2/resolve/main/model.bin?download=true",
	    "F3C87256A2C888100C179D7DCD7F41DF17C767469546C59D32C7DDE86C740A6B"},
	   {
		   "https://huggingface.co/santhosh/madlad400-3b-ct2/resolve/main/config.json?download=true",
		   "A428C51CD35517554523B3C6B6974A5928BC35E82B130869A543566A34A83B93",
	   },
	   {"https://huggingface.co/santhosh/madlad400-3b-ct2/resolve/main/shared_vocabulary.txt?download=true",
	    "C327551CE3CA6EFC7B437E11A267F79979893332DDA8A1D146E2C950815193F8"},
	   {"https://huggingface.co/santhosh/madlad400-3b-ct2/resolve/main/sentencepiece.model?download=true",
	    "EF11AC9A22C7503492F56D48DCE53BE20E339B63605983E9F27D2CD0E0F3922C"}}}},
	{"Whisper Base q5 (57Mb)",
	 {"Whisper Base q5",
	  "whisper-base-q5",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-base-q5_1.bin",
	    "422F1AE452ADE6F30A004D7E5C6A43195E4433BC370BF23FAC9CC591F01A8898"}}}},
	{"Whisper Base English q5 (57Mb)",
	 {"Whisper Base En q5",
	  "ggml-model-whisper-base-en-q5_1",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-base.en-q5_1.bin",
	    "4BAF70DD0D7C4247BA2B81FAFD9C01005AC77C2F9EF064E00DCF195D0E2FDD2F"}}}},
	{"Whisper Base (141Mb)",
	 {"Whisper Base",
	  "ggml-model-whisper-base",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-base.bin",
	    "60ED5BC3DD14EEA856493D334349B405782DDCAF0028D4B5DF4088345FBA2EFE"}}}},
	{"Whisper Base English (141Mb)",
	 {"Whisper Base En",
	  "ggml-model-whisper-base-en",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-base.en.bin",
	    "A03779C86DF3323075F5E796CB2CE5029F00EC8869EEE3FDFB897AFE36C6D002"}}}},
	{"Whisper Large v1 q5 (1Gb)",
	 {"Whisper Large v1 q5",
	  "ggml-model-whisper-large-q5_0",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-large-q5_0.bin",
	    "3A214837221E4530DBC1FE8D734F302AF393EB30BD0ED046042EBF4BAF70F6F2"}}}},
	{"Whisper Medium q5 (514Mb)",
	 {"Whisper Medium q5",
	  "ggml-model-whisper-medium-q5_0",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-medium-q5_0.bin",
	    "19FEA4B380C3A618EC4723C3EEF2EB785FFBA0D0538CF43F8F235E7B3B34220F"}}}},
	{"Whisper Medium English q5 (514Mb)",
	 {"Whisper Medium En q5",
	  "ggml-model-whisper-medium-en-q5_0",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-medium.en-q5_0.bin",
	    "76733E26AD8FE1C7A5BF7531A9D41917B2ADC0F20F2E4F5531688A8C6CD88EB0"}}}},
	{"Whisper Small q5 (181Mb)",
	 {"Whisper Small q5",
	  "ggml-model-whisper-small-q5_1",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-small-q5_1.bin",
	    "AE85E4A935D7A567BD102FE55AFC16BB595BDB618E11B2FC7591BC08120411BB"}}}},
	{"Whisper Small English q5 (181Mb)",
	 {"Whisper Small En q5",
	  "ggml-model-whisper-small-en-q5_1",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-small.en-q5_1.bin",
	    "BFDFF4894DCB76BBF647D56263EA2A96645423F1669176F4844A1BF8E478AD30"}}}},
	{"Whisper Small (465Mb)",
	 {"Whisper Small",
	  "ggml-model-whisper-small",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-small.bin",
	    "1BE3A9B2063867B937E64E2EC7483364A79917E157FA98C5D94B5C1FFFEA987B"}}}},
	{"Whisper Small English (465Mb)",
	 {"Whisper Small En",
	  "ggml-model-whisper-small-en",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-small.en.bin",
	    "C6138D6D58ECC8322097E0F987C32F1BE8BB0A18532A3F88F734D1BBF9C41E5D"}}}},
	{"Whisper Tiny (74Mb)",
	 {"Whisper Tiny",
	  "ggml-model-whisper-tiny",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-tiny.bin",
	    "BE07E048E1E599AD46341C8D2A135645097A538221678B7ACDD1B1919C6E1B21"}}}},
	{"Whisper Tiny q5 (31Mb)",
	 {"Whisper Tiny q5",
	  "ggml-model-whisper-tiny-q5_1",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-tiny-q5_1.bin",
	    "818710568DA3CA15689E31A743197B520007872FF9576237BDA97BD1B469C3D7"}}}},
	{"Whisper Tiny English q5 (31Mb)",
	 {"Whisper Tiny En q5",
	  "ggml-model-whisper-tiny-en-q5_1",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-tiny.en-q5_1.bin",
	    "C77C5766F1CEF09B6B7D47F21B546CBDDD4157886B3B5D6D4F709E91E66C7C2B"}}}},
	{"Whisper Tiny English q8 (42Mb)",
	 {"Whisper Tiny En q8",
	  "ggml-model-whisper-tiny-en-q8_0",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-tiny.en-q8_0.bin",
	    "5BC2B3860AA151A4C6E7BB095E1FCCE7CF12C7B020CA08DCEC0C6D018BB7DD94"}}}},
	{"Whisper Tiny English (74Mb)",
	 {"Whisper Tiny En",
	  "ggml-model-whisper-tiny-en",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://ggml.ggerganov.com/ggml-model-whisper-tiny.en.bin",
	    "921E4CF8686FDD993DCD081A5DA5B6C365BFDE1162E72B08D75AC75289920B1F"}}}},
	{"Whisper Large v3 (3Gb)",
	 {"Whisper Large v3",
	  "ggml-large-v3",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-large-v3.bin",
	    "64d182b440b98d5203c4f9bd541544d84c605196c4f7b845dfa11fb23594d1e2"}}}},
	{"Whisper Large v3 q5 (1Gb)",
	 {"Whisper Large v3 q5",
	  "ggml-large-v3-q5_0",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-large-v3-q5_0.bin",
	    "d75795ecff3f83b5faa89d1900604ad8c780abd5739fae406de19f23ecd98ad1"}}}},
	{"Whisper Large v2 (3Gb)",
	 {"Whisper Large v2",
	  "ggml-large-v2",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-large-v2.bin",
	    "9a423fe4d40c82774b6af34115b8b935f34152246eb19e80e376071d3f999487"}}}},
	{"Whisper Large v1 (3Gb)",
	 {"Whisper Large v1",
	  "ggml-large-v1",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-large-v1.bin",
	    "7d99f41a10525d0206bddadd86760181fa920438b6b33237e3118ff6c83bb53d"}}}},
	{"Whisper Medium English (1.5Gb)",
	 {"Whisper Medium English",
	  "ggml-medium-en",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-medium.en.bin",
	    "cc37e93478338ec7700281a7ac30a10128929eb8f427dda2e865faa8f6da4356"}}}},
	{"Whisper Medium (1.5Gb)",
	 {"Whisper Medium",
	  "ggml-medium",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-medium.bin",
	    "6c14d5adee5f86394037b4e4e8b59f1673b6cee10e3cf0b11bbdbee79c156208"}}}},
	{"Whisper Large v3 Turbo (1.62Gb)",
	 {"Whisper Large v3 Turbo",
	  "ggml-large-v3-turbo",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-large-v3-turbo.bin",
	    "1FC70F774D38EB169993AC391EEA357EF47C88757EF72EE5943879B7E8E2BC69"}}}},
	{"Whisper Large v3 Turbo q5 (574Mb)",
	 {"Whisper Large v3 Turbo q5",
	  "ggml-large-v3-turbo-q5_0",
	  MODEL_TYPE_TRANSCRIPTION,
	  {{"https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-large-v3-turbo-q5_0.bin",
	    "394221709CD5AD1F40C46E6031CA61BCE88931E6E088C188294C6D5A55FFA7E2"}}}},
}};
