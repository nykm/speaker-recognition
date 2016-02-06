#include "VQRecognizer.h"
#include "Utilities.h"
#include "VQModel.h"

VQRecognizer::VQRecognizer()
{

}

VQRecognizer::~VQRecognizer()
{

}

void VQRecognizer::Train(const std::shared_ptr<SpeechData>& data)
{
    ModelRecognizer<VQModel>::Train(data);

    // Is this necessary?
    if (IsBackgroundModelEnabled() && GetBackgroundModel() != nullptr)
    {
        GetBackgroundModel()->Weight(GetSpeakerModels());
    }

    for (auto& model : GetSpeakerModels())
    {
        model.second->Weight(GetSpeakerModels());
    }
}

void VQRecognizer::Test(const std::shared_ptr<SpeechData>& data, std::map<std::string, RecognitionResult>& results)
{
    ModelRecognizer<VQModel>::Test(data, results);
}

std::vector<Real> VQRecognizer::Verify(const std::string& speaker, const std::shared_ptr<SpeechData>& data)
{
    return ModelRecognizer<VQModel>::GetMultipleVerificationScore(speaker, data);
}

void VQRecognizer::SaveTrainedData(const std::string& path)
{
    //std::ofstream outFile;

    //outFile.open(path);

    //for (const auto& entry : mCodebooks)
    //{
    //    const auto& centroids = entry.second.clusterCentroids;
    //    const auto& sizes = entry.second.clusterSizes;
    //    const auto& weights = entry.second.clusterWeights;

    //    outFile << entry.first << " ";

    //    for (unsigned int c = 0; c < centroids.size(); c++)
    //    {
    //        outFile << weights[c] << " ";

    //        for (unsigned int i = 0; i < centroids[c].GetSize(); i++)
    //        {
    //            outFile << centroids[c][i];

    //            if (i + 1 != centroids[c].GetSize())
    //            {
    //                outFile << " ";
    //            }
    //        }

    //        if (c + 1 != centroids.size())
    //        {
    //            outFile << ",";
    //        }
    //    }

    //    outFile << std::endl;
    //}
}

void VQRecognizer::LoadTrainedData(const std::string& path)
{
    //mCodebooks.clear();

    //std::ifstream inFile;

    //inFile.open(path);

    //std::string line;

    //while(std::getline(inFile, line))
    //{
    //    std::stringstream ssFeatures(line);

    //    std::string label;

    //    if (ssFeatures >> label)
    //    {
    //        std::cout << "Loading model: " << label << std::endl;

    //        std::string features;

    //        auto& codebook = mCodebooks[label];

    //        while (std::getline(ssFeatures, features, ','))
    //        {
    //            codebook.clusterCentroids.emplace_back();
    //            codebook.clusterSizes.emplace_back();
    //            codebook.clusterWeights.emplace_back();

    //            std::stringstream ssFeature(features);
    //            std::string feature;

    //            if (ssFeature >> feature)
    //            {
    //                std::cout << "weight:" << ConvertString<Real>(feature) << std::endl;
    //                codebook.clusterWeights.back() = ConvertString<Real>(feature);
    //            }

    //            while (std::getline(ssFeature, feature, ' '))
    //            {
    //                if (feature.size() > 0 && feature[0] != ' ')
    //                {
    //                    codebook.clusterCentroids.back().Push(ConvertString<Real>(feature));
    //                }
    //            }

    //            codebook.clusterSizes.back() = 1;

    //            if (codebook.clusterCentroids.back().GetSize() == 0)
    //            {
    //                codebook.clusterCentroids.pop_back();
    //                codebook.clusterSizes.pop_back();
    //                codebook.clusterWeights.pop_back();
    //            }
    //        }

    //        if (codebook.clusterCentroids.size() == 0)
    //        {
    //            mCodebooks.erase(label);

    //            std::cout << "Error: missing sample data." << std::endl;
    //        }

    //        std::cout
    //            << "current codebook: " << label
    //            << "added codebook count: " << mCodebooks.size()
    //            << ", codebook centroids: " << codebook.clusterCentroids.size()
    //            << std::endl;
    //    }
    //}
}
